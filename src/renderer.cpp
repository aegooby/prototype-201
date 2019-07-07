
#include	"__common.hpp"
#include	"renderer.hpp"
#include	"entity.hpp"
#include	"filesystem.hpp"

__begin_ns_td

void	renderer::load_sprite(SDL_Texture*& texture, const std::string& path)
{
	texture = IMG_LoadTexture(__sdl_renderer, path.c_str());
	if (!texture)
		throw sdl_error("Failed to load texture");
}
void	renderer::load_flipbook(sprite_flipbook& flipbook, const std::string& path)
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

void	renderer::load(std::list<std::unique_ptr<entity>>& entities, const std::string& path)
{
	std::string	__path = path;
	if (__path.back() != TD_DIRECTORY_SLASH)
		__path += TD_DIRECTORY_SLASH;
	for (auto& entity : entities)
	{
		auto	ptr = entity.get();
		if (typeid(*ptr) == typeid(character) || typeid(*ptr) == typeid(player))
		{
			auto	render_component = dynamic_cast<actor*>(entity.get())->render.lock();
			if (!render_component.get())
				throw std::runtime_error("Pointer was not allocated");
			directory	__directory(directory::mode::read_only, __path + entity->name());
			__directory.read();
			for (auto& entry : __directory.entries())
			{
				if (directory::is_directory(__directory.path() + entry))
				{
					render_component->add_flipbook(entry, 10.0f);
					load_flipbook(render_component->flipbooks.at(entry), __directory.path() + entry);
				}
			}
		}
	}
}

void	renderer::render_sprite(SDL_Texture* texture, SDL_Rect* rect)
{
	if (SDL_RenderCopy(__sdl_renderer, texture, nullptr, rect))
		throw sdl_error("Failed to render texture");
}

void	renderer::render_flipbook(sprite_flipbook& flipbook, SDL_Rect* rect)
{
	render_sprite(flipbook.textures.at(flipbook.index), rect);
	++flipbook.framec %= flipbook.frame_delay();
	if (!flipbook.framec)
		++flipbook.index %= flipbook.frames();
}

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
		if (typeid(*ptr) == typeid(character) || typeid(*ptr) == typeid(player))
		{
			auto	render_component = dynamic_cast<actor*>(entity.get())->render.lock();
			if (!render_component.get())
				throw std::runtime_error("Pointer was not allocated");
			for (auto& flipbook : render_component->flipbooks)
			{
				render_flipbook(flipbook.second, &(render_component->rect));
			}
		}
	}
	// Hey this is IMPORTANT!
	SDL_RenderPresent(__sdl_renderer);
}

__end_ns_td
