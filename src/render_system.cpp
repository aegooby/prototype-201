
#include	"__common.hpp"
#include	"render_system.hpp"
#include	"entity.hpp"
#include	"filesystem.hpp"
#include	"entity_manager.hpp"
#include	"world.hpp"

__begin_ns_td

void	render_system::load_sprite(SDL_Texture*& texture, const std::string& path)
{
	texture = IMG_LoadTexture(__sdl_renderer, path.c_str());
	if (!texture)
		throw sdl_error("Failed to load texture");
}
void	render_system::load_flipbook(sprite_flipbook& flipbook, const std::string& path)
{
	directory	__directory(directory::mode::read_only, path);
	__directory.read();
	
	for (uint32_t i = 0; i < __directory.entries().size(); ++i)
	{
		flipbook.paths.push_back(__directory.path() + std::to_string(i) + ".png");
	}
	for (auto& path : flipbook.paths)
	{
		flipbook.textures.emplace_back(nullptr);
		load_sprite(flipbook.textures.back(), path);
	}
}

void	render_system::load(const std::string& path)
{
	std::string	__path = path;
	if (__path.back() != TD_DIRECTORY_SLASH)
		__path += TD_DIRECTORY_SLASH;
	for (auto& entity : __registered_entities)
	{
		auto&	render = entity.get().component<render_component>();
		directory	__directory(directory::mode::read_only, __path + entity.get().name());
		__directory.read();
		for (auto& entry : __directory.entries())
		{
			if (directory::is_directory(__directory.path() + entry))
			{
				render.add_flipbook(entry, 10.0f);
				load_flipbook(render.flipbooks.at(entry), __directory.path() + entry);
			}
		}
	}
}

void	render_system::render_sprite(SDL_Texture* texture, SDL_Rect* rect)
{
	if (SDL_RenderCopy(__sdl_renderer, texture, nullptr, rect))
		throw sdl_error("Failed to render texture");
}

void	render_system::render_flipbook(sprite_flipbook& flipbook, SDL_Rect* rect)
{
	render_sprite(flipbook.textures.at(flipbook.index), rect);
	++flipbook.framec %= flipbook.frame_delay();
	if (!flipbook.framec)
		++flipbook.index %= flipbook.frames();
}

void	render_system::render()
{
	if (SDL_SetRenderDrawColor(__sdl_renderer, 0, 0, 255, 255))
		throw sdl_error("Failed to set draw color");
	if (SDL_RenderClear(__sdl_renderer))
		throw sdl_error("Failed to clear render_system");
	
	// TODO: temp (it just renders all flipbooks)
	for (auto& entity : __registered_entities)
	{
		auto&	render = entity.get().component<render_component>();
		auto&	transform = entity.get().component<transform_component>();
		render.rect.x = transform.position.x();
		render.rect.y = transform.position.y();
		for (auto& flipbook : render.flipbooks)
		{
			render_flipbook(flipbook.second, &(render.rect));
		}
	}
	// Hey this is IMPORTANT!
	SDL_RenderPresent(__sdl_renderer);
}

__end_ns_td
