
#include	"__common.hpp"
#include	"input.hpp"
#include	"window.hpp"

__begin_ns_td

void	mouse::position(float x, float y)
{
	__position.x = x;
	__position.y = y;
	SDL_WarpMouseInWindow(window_context.sdl_window(), int(__position.x), int(__position.y));
}
void	mouse::position(const vector_2& position)
{
	__position = position;
	SDL_WarpMouseInWindow(window_context.sdl_window(), int(__position.x), int(__position.y));
}

__end_ns_td
