
#pragma	once
#include	"__common.hpp"
#include	"window.hpp"
#include	"exception.hpp"
#include	"system.hpp"
#include	<unordered_map>

__begin_ns_td

class	render_system : public system
{
public:
	using __base = system;
protected:
	SDL_Renderer*	__sdl_renderer = nullptr;
protected:
	void	load_sprite(SDL_Texture*&, const std::string&);
	void	load_flipbook(sprite_flipbook&, const std::string&);
	void	render_sprite(SDL_Texture*, SDL_Rect*);
	void	render_flipbook(sprite_flipbook&, SDL_Rect*);
public:
	render_system(class world& world) : __base(world)
	{
		flag.set(system::flag::render);
		flag.set(system::flag::transform);
	}
	virtual ~render_system()
	{
		stop();
	}
	inline __attribute__((always_inline))
	void	start(class window& window)
	{
		if (!(__sdl_renderer = SDL_CreateRenderer(window.sdl_window(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
			throw sdl_error("Failed to create render_system");
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
	void	load(const std::string&);
	virtual void	update() override {  }
	void	render();
	
	//	Preventing copying and moving
	render_system(const render_system&) = delete;
	render_system(render_system&&) = delete;
	render_system&	operator =(const render_system&) = delete;
	render_system&	operator =(render_system&&) = delete;
};

__end_ns_td
