
#include "input.hpp"

#include "../__common.hpp"
#include "../core.hpp"

namespace p201
{

void mouse::position(float x, float y)
{
    __position.x() = x;
    __position.x() = y;
    SDL_WarpMouseInWindow(window_context.sdl_window(), int(__position.x()),
                          int(__position.y()));
}
void mouse::position(const vector_2& position)
{
    __position = position;
    SDL_WarpMouseInWindow(window_context.sdl_window(), int(__position.x()),
                          int(__position.y()));
}

} // namespace p201
