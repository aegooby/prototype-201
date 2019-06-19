
#pragma	once

#include	"__common.hpp"
#include	"input.hpp"

__begin_ns_td

class	sdl_error : public std::runtime_error
{
public:
	explicit sdl_error(const std::string& what) noexcept : std::runtime_error(what) {  }
	explicit sdl_error(const char* what) noexcept : std::runtime_error(what) {  }
	virtual ~sdl_error() = default;
};

class	window
{
protected:
	std::string		__title = std::string();
	int				__width = int(), __height = int();
	SDL_Window*		__sdl_window = nullptr;
	bool			__closed = false;
	SDL_SysWMinfo	__syswm_info = SDL_SysWMinfo();
public:
	keyboard		keyboard;
	mouse			mouse;
	window(const std::string& title, int width, int height) : __title(title), __width(width), __height(height), keyboard(*this), mouse(*this)	{  }
	~window()
	{
		stop();
	}
	inline __attribute__((always_inline))
	void	start()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING))
			throw sdl_error("Failed to initialize SDL");
		if (!(__sdl_window = SDL_CreateWindow(__title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, __width, __height, SDL_WINDOW_ALLOW_HIGHDPI)))
			throw std::runtime_error("Failed to create window");
		
		SDL_GetVersion(&__syswm_info.version);
		SDL_GetWindowWMInfo(__sdl_window, &__syswm_info);
	}
	inline __attribute__((always_inline))
	void	stop()
	{
		if (__sdl_window)
		{
			SDL_DestroyWindow(__sdl_window);
			__sdl_window = nullptr;
		}
		SDL_Quit();
	}
	inline __attribute__((always_inline))
	const std::string&	title()
	{
		return __title;
	}
	inline __attribute__((always_inline))
	SDL_Window*	sdl_window()
	{
		return __sdl_window;
	}
	inline __attribute__((always_inline))
	bool	closed() const
	{
		return __closed;
	}
	inline __attribute__((always_inline))
	int	width() const
	{
		return __width;
	}
	inline __attribute__((always_inline))
	int	height() const
	{
		return __height;
	}
	inline __attribute__((always_inline))
	const SDL_SysWMinfo&	syswm_info() const
	{
		return __syswm_info;
	}
	inline __attribute__((always_inline))
	void	update()
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
	
	//	Preventing copying and moving
	window(const window&) = delete;
	window(const window&&) = delete;
	window&	operator =(const window&) = delete;
	window&	operator =(const window&&) = delete;
};

__end_ns_td
