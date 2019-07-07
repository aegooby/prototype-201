
#pragma	once
#include	"__common.hpp"
#include	"window.hpp"
#include	"exception.hpp"
#include	<list>

__begin_ns_td

class	renderer
{
protected:
	window&			window_context;
	SDL_Renderer*	__sdl_renderer = nullptr;
protected:
	void	load_sprite(SDL_Texture*&, const std::string&);
	void	load_flipbook(sprite_flipbook&, const std::string&);
	void	render_sprite(SDL_Texture*, SDL_Rect*);
	void	render_flipbook(sprite_flipbook&, SDL_Rect*);
public:
	renderer(window& window_context) : window_context(window_context)	{  }
	~renderer()
	{
		stop();
	}
	inline __attribute__((always_inline))
	void	start()
	{
		if (!(__sdl_renderer = SDL_CreateRenderer(window_context.sdl_window(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
			throw sdl_error("Failed to create renderer");
		if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP))
			throw sdl_error("Failed to load SDL Image libraries");
	}
	inline __attribute__((always_inline))
	void	stop()
	{
		if (__sdl_renderer)
		{
			SDL_DestroyRenderer(__sdl_renderer);
			__sdl_renderer = nullptr;
		}
		IMG_Quit();
	}
	inline __attribute__((always_inline))
	SDL_Renderer*	sdl_renderer()
	{
		return __sdl_renderer;
	}
	void	render(std::list<std::unique_ptr<entity>>&);
	void	load(std::list<std::unique_ptr<entity>>&, const std::string&);
	
	//	Preventing copying and moving
	renderer(const renderer&) = delete;
	renderer(renderer&&) = delete;
	renderer&	operator =(const renderer&) = delete;
	renderer&	operator =(renderer&&) = delete;
};

__end_ns_td
