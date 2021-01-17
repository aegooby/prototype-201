
#include "window.hpp"

namespace p201
{
window::window(const std::string& title)
    : __title(title), keyboard(*this), mouse(*this)
{ }
window::~window()
{
    stop();
}
void window::start()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
        throw sdl_error("Failed to initialize SDL");
    if (!(__sdl_window =
              SDL_CreateWindow(__title.c_str(), SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, width, height, 0x0)))
        throw sdl_error("Failed to create window");

    SDL_GetVersion(&__syswm_info.version);
    SDL_GetWindowWMInfo(__sdl_window, &__syswm_info);
}
void window::stop()
{
    if (__sdl_window)
    {
        SDL_DestroyWindow(__sdl_window);
        __sdl_window = nullptr;
    }
    SDL_Quit();
}
const std::string& window::title()
{
    return __title;
}
SDL_Window* window::sdl_window()
{
    return __sdl_window;
}
bool window::closed() const
{
    return __closed;
}
const SDL_SysWMinfo& window::syswm_info() const
{
    return __syswm_info;
}
void window::update()
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
} // namespace p201
