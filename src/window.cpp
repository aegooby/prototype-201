
#include	"__common.hpp"
#include	"window.hpp"

__begin_ns_td

void	window::update()
{
	keyboard.key_down_clear();
	keyboard.key_up_clear();
	mouse.button_down_clear();
	mouse.button_up_clear();
	mouse.update();
	
	SDL_Event	event;
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_WINDOWEVENT_CLOSE: case SDL_QUIT:
				__closed = true;
				break;
			case SDL_KEYDOWN:
				keyboard.key_down(keycode(event.key.keysym.scancode), true);
				keyboard.key_scan(keycode(event.key.keysym.scancode), true);
				break;
			case SDL_KEYUP:
				keyboard.key_up(keycode(event.key.keysym.scancode), true);
				keyboard.key_scan(keycode(event.key.keysym.scancode), false);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse.button_down(mousecode(event.button.button), true);
				mouse.button_scan(mousecode(event.button.button), true);
				break;
			case SDL_MOUSEBUTTONUP:
				mouse.button_up(mousecode(event.button.button), true);
				mouse.button_scan(mousecode(event.button.button), false);
				break;
		}
	}
}

__end_ns_td
