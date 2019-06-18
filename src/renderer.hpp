
#pragma	once
#include	"__common.hpp"
#include	"window.hpp"

__begin_ns_td

class	renderer
{
protected:
	window&			window_context;
	SDL_Renderer*	__sdl_renderer = nullptr;
public:
	renderer(window& window_context) : window_context(window_context)	{  }
	~renderer()
	{
		stop();
	}
	inline __attribute__((always_inline))
	void	start()
	{
		if (!(__sdl_renderer = SDL_CreateRenderer(window_context.sdl_window(), -1, SDL_RENDERER_PRESENTVSYNC)))
			throw std::runtime_error("Failed to create renderer");
		if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP))
			throw std::runtime_error("Failed to load SDL Image libraries");
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
	template	<template <typename, typename...> class container, typename ... args>
	void	render(container<std::unique_ptr<game_object>, args...>& game_objects)
	{
		if (SDL_SetRenderDrawColor(__sdl_renderer, 200, 100, 50, 255))
			throw std::runtime_error("Failed to set draw color");
		if (SDL_RenderClear(__sdl_renderer))
			throw std::runtime_error("Failed to clear renderer");
		for (auto& game_object : game_objects)
		{
			game_object->draw(*this);
		}
	}
	
	//	Preventing copying and moving
	renderer(const renderer&) = delete;
	renderer(const renderer&&) = delete;
	renderer&	operator =(const renderer&) = delete;
	renderer&	operator =(const renderer&&) = delete;
};

__end_ns_td
