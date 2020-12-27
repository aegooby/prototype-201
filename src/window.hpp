
#pragma once
#include "__common.hpp"
#include "exception.hpp"
#include "input.hpp"

namespace p201
{

class window
{
protected:
    std::string   __title      = std::string();
    SDL_Window*   __sdl_window = nullptr;
    bool          __closed     = false;
    SDL_SysWMinfo __syswm_info = SDL_SysWMinfo();

public:
    static constexpr int width  = 1366;
    static constexpr int height = 768;

    keyboard keyboard;
    mouse    mouse;
    window(const std::string& title)
        : __title(title), keyboard(*this), mouse(*this)
    {
    }
    ~window()
    {
        stop();
    }
    inline __attribute__((always_inline)) void start()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING))
            throw sdl_error("Failed to initialize SDL");
        // TODO: should we work with SDL_WINDOW_ALLOW_HIGHDPI?
        if (!(__sdl_window =
                  SDL_CreateWindow(__title.c_str(), SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, width, height, 0x0)))
            throw sdl_error("Failed to create window");

        SDL_GetVersion(&__syswm_info.version);
        SDL_GetWindowWMInfo(__sdl_window, &__syswm_info);
    }
    inline __attribute__((always_inline)) void stop()
    {
        if (__sdl_window)
        {
            SDL_DestroyWindow(__sdl_window);
            __sdl_window = nullptr;
        }
        SDL_Quit();
    }
    inline __attribute__((always_inline)) const std::string& title()
    {
        return __title;
    }
    inline __attribute__((always_inline)) SDL_Window* sdl_window()
    {
        return __sdl_window;
    }
    inline __attribute__((always_inline)) bool closed() const
    {
        return __closed;
    }
    inline __attribute__((always_inline)) const SDL_SysWMinfo&
    syswm_info() const
    {
        return __syswm_info;
    }
    inline __attribute__((always_inline)) void update()
    {
        keyboard.down_clear();
        keyboard.up_clear();
        keyboard.update();

        mouse.down_clear();
        mouse.up_clear();
        mouse.update();

        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            keycode   __keycode   = keycode(event.key.keysym.scancode);
            mousecode __mousecode = mousecode(event.button.button);
            switch (event.type)
            {
                case SDL_WINDOWEVENT_CLOSE:
                case SDL_QUIT:
                    __closed = true;
                    break;
                case SDL_KEYDOWN:
                    if (!event.key.repeat) keyboard.down_set(true, __keycode);
                    keyboard.scan_set(true, __keycode);
                    break;
                case SDL_KEYUP:
                    keyboard.up_set(true, __keycode);
                    keyboard.scan_set(false, __keycode);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouse.down_set(true, __mousecode);
                    mouse.scan_set(true, __mousecode);
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouse.up_set(true, __mousecode);
                    mouse.scan_set(false, __mousecode);
                    break;
            }
        }
    }

    //	Preventing copying and moving
    window(const window&) = delete;
    window(window&&)      = delete;
    window& operator=(const window&) = delete;
    window& operator=(window&&) = delete;
};

} // namespace p201
