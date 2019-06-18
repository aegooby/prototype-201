
#pragma	once
#include	"__common.hpp"
#include	"renderer.hpp"

__begin_ns_td

class	game_object
{
protected:
	float	__x = 0.0f, __y = 0.0f;
	float	__w = 0.0f, __h = 0.0f;
public:
	game_object() = default;
	game_object(float x, float y, float w, float h) : __x(x), __y(y), __w(w), __h(h)	{  }
	virtual ~game_object() = default;
	virtual void	draw(td::renderer& renderer) = 0;
	virtual void	update() = 0;
};

class	character : public game_object
{
protected:
	using __base = game_object;
	float		__vx = 0.0f, __vy = 0.0f;
	SDL_Rect	__rect;
public:
	character() = default;
	character(float x, float y, float w, float h) : __base(x, y, w, h)	{  }
	virtual ~character() = default;
	virtual void	draw(td::renderer& renderer)
	{
		__rect = { int(__x), int(__y), int(__w), int(__h) };
		if (SDL_SetRenderDrawColor(renderer.sdl_renderer(), 255, 255, 255, 255))
			throw std::runtime_error("Failed to set draw color");
		if (SDL_RenderFillRect(renderer.sdl_renderer(), &__rect))
			throw std::runtime_error("Failed to fill rectangle");
	}
	virtual void	update()
	{
		__x += __vx;
		__y += __vy;
	}
};

__end_ns_td
