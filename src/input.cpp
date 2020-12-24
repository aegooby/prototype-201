
#include "input.hpp"

#include "__common.hpp"
#include "window.hpp"

namespace p201
{

void mouse::position(float x, float y)
{
    __position[0] = x;
    __position[1] = y;
    SDL_WarpMouseInWindow(window_context.sdl_window(), int(__position[0]),
                          int(__position[1]));
}
void mouse::position(const vector_2& position)
{
    __position = position;
    SDL_WarpMouseInWindow(window_context.sdl_window(), int(__position[0]),
                          int(__position[1]));
}

} // namespace p201
