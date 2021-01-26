
#include "window.hpp"

namespace p201
{
window::window(const std::string& title)
    : title(title), keyboard(*this), mouse(*this)
{ }
window::~window()
{
    stop();
}
void window::start()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
        throw sdl_error("Failed to initialize SDL");

    std::uint32_t flags = SDL_WINDOW_VULKAN;
    auto          pos   = SDL_WINDOWPOS_CENTERED;

    handle = SDL_CreateWindow(title.c_str(), pos, pos, width, height, flags);
    if (!handle) throw sdl_error("Failed to create window");
}
void window::stop()
{
    if (handle)
    {
        SDL_DestroyWindow(handle);
        handle = nullptr;
    }
    SDL_Quit();
}
bool window::closed() const
{
    return __closed;
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
