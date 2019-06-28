
#include	"__common.hpp"
#include	"renderer.hpp"
#include	"entity.hpp"

__begin_ns_td

void	renderer::render(std::list<std::unique_ptr<entity>>& entities)
{
	if (SDL_SetRenderDrawColor(__sdl_renderer, 0, 0, 255, 255))
		throw sdl_error("Failed to set draw color");
	if (SDL_RenderClear(__sdl_renderer))
		throw sdl_error("Failed to clear renderer");
	
	// TODO: temp
	for (auto& entity : entities)
	{
		auto	ptr = entity.get();
		if (typeid(*ptr) == typeid(character))
		{
			dynamic_cast<actor*>(entity.get())->render->render(*this);
		}
	}
	// Hey this is IMPORTANT!
	SDL_RenderPresent(__sdl_renderer);
}

__end_ns_td
