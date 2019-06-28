
#include	"__common.hpp"
#include	"sprite.hpp"
#include	"filesystem.hpp"
#include	"component.hpp"

__begin_ns_td

sprite_base::~sprite_base() = default;

void	sprite::create(td::renderer& renderer, const std::string& path)
{
	__texture = IMG_LoadTexture(renderer.sdl_renderer(), path.c_str());
	if (!__texture)
		throw sdl_error(std::string("Failed to load texture, sprite: ") + __name);
}

void	sprite::render(td::renderer& renderer, render_component& parent)
{
	if (SDL_RenderCopy(renderer.sdl_renderer(), __texture, nullptr, parent.rect_addr()))
		throw sdl_error(std::string("Failed to render texture: 0x") + std::to_string(long(__texture)) + std::string(", sprite: ") + __name);
}

void	sprite_flipbook::create(td::renderer& renderer, const std::string& directory_path)
{
	directory	__directory(directory::mode::read_only, directory_path);
	__directory.read();
	std::string	__path = __directory.path();
	__directory.close();
	
	for (uint32_t i = 0; i < __directory.entries().size(); ++i)
	{
		if (__path.back() == TD_DIRECTORY_SLASH)
			__paths.push_back(__path + std::to_string(i) + ".png");
		else
			__paths.push_back(__path + TD_DIRECTORY_SLASH + std::to_string(i) + ".png");
	}
	for (auto& path : __paths)
	{
		__sprites.emplace_back(sprite(path));
		__sprites.back().create(renderer, path);
	}
}

void	sprite_flipbook::render(td::renderer& renderer, render_component& parent)
{
	__sprites.at(__index).render(renderer, parent);
	size_t	frame_delay = size_t(1.0f / __fps * global::game_fps);
	++__framec %= frame_delay;
	if (!__framec)
		++__index %= __sprites.size();
}

__end_ns_td
