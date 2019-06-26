
#include	"__common.hpp"
#include	"sprite.hpp"
#include	"filesystem.hpp"
#include	"component.hpp"

__begin_ns_td

sprite_base::~sprite_base() = default;

void	sprite::create(td::renderer& renderer, const std::string& path)
{
	__texture = IMG_LoadTexture(renderer.sdl_renderer(), path.c_str());
}

void	sprite::render(td::renderer& renderer, render_component& parent)
{
	SDL_RenderCopy(renderer.sdl_renderer(), __texture, nullptr, parent.rect_addr());
}

void	sprite_flipbook::create(td::renderer& renderer, const std::string& directory_path)
{
	directory	__directory(directory::mode::read_only, directory_path);
	__directory.read();
	__directory.close();
	
	for (uint32_t i = 0; i < __directory.entries().size(); ++i)
	{
		__paths.push_back(__directory.path() + std::to_string(i));
	}
	for (auto& path : __paths)
	{
		__sprites.emplace_back(path);
		__sprites.back().create(renderer, path);
	}
}

void	sprite_flipbook::render(td::renderer& renderer, render_component& parent)
{
	if (!__frame_delay)
		throw std::runtime_error("Frame delay not set");
	__sprites.at(__index).render(renderer, parent);
	++__framec %= __frame_delay;
	if (!__framec)
		++__index %= __sprites.size();
}

__end_ns_td
