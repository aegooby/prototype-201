
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
		flag.set(system::flag::state);
	}
	virtual ~render_system()
	{
		stop();
	}
	virtual void	start() override;
	void	start(class window&);
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
