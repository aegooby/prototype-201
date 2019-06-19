
#include	"__common.hpp"
#include	"component.hpp"
#include	"renderer.hpp"

__begin_ns_td

component::~component() = default;

sprite_component::~sprite_component()
{
	if (__surface)
		SDL_FreeSurface(__surface);
}
void	sprite_component::load(td::renderer& renderer)
{
	if (__surface)
		SDL_CreateTextureFromSurface(renderer.sdl_renderer(), __surface);
}
void	sprite_component::render(td::renderer& renderer)
{
	SDL_RenderCopy(renderer.sdl_renderer(), __texture, nullptr, &__rect);
}

__end_ns_td
