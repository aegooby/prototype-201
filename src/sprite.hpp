
#pragma	once
#include	"__common.hpp"
#include	"renderer.hpp"
#include	<vector>

__begin_ns_td

class	sprite_flipbook
{
public:
	std::vector<SDL_Texture*>	textures;
	std::vector<std::string>	paths;
	uint32_t	framec = 0;
	uint32_t	index = 0;
protected:
	const std::string	__name;
	float				__fps = 0;
public:
	sprite_flipbook(const std::string& name, float fps = 10.0f) : __name(name), __fps(fps)
	{
		if (__fps <= 0 || __fps > float(global::game_fps))
			throw std::runtime_error(std::string("Invalid fps, flipbook: ") + __name);
	}
	sprite_flipbook(sprite_flipbook&& other) : paths(std::move(other.paths)), __name(other.__name), __fps(other.__fps)
	{
		for (auto& texture : other.textures)
		{
			textures.emplace_back(texture);
			texture = nullptr;
		}
	}
	sprite_flipbook&	operator =(sprite_flipbook&& other)
	{
		paths = std::move(other.paths);
		__fps = other.__fps;
		for (auto& texture : other.textures)
		{
			textures.emplace_back(texture);
			texture = nullptr;
		}
		return *this;
	}
	virtual ~sprite_flipbook()
	{
		for (auto& texture : textures)
		{
			if (texture)
			{
				SDL_DestroyTexture(texture);
			}
		}
	}
	inline __attribute__((always_inline))
	virtual const std::string&	name() const
	{
		return __name;
	}
	inline __attribute__((always_inline))
	void	fps(float fps)
	{
		if (__fps <= 0 || __fps > float(global::game_fps))
			throw std::runtime_error(std::string("Invalid fps, flipbook: ") + __name);
		__fps = fps;
	}
	inline __attribute__((always_inline))
	float	fps() const
	{
		return __fps;
	}
	inline __attribute__((always_inline))
	size_t	frame_delay() const
	{
		return size_t(1.0f / __fps * global::game_fps);
	}
	inline __attribute__((always_inline))
	size_t	frames() const
	{
		return textures.size();
	}
	inline __attribute__((always_inline))
	float	seconds() const
	{
		return 1.0f / __fps * frames();
	}
	
	// Preventing copying
	sprite_flipbook(const sprite_flipbook&) = delete;
	sprite_flipbook&	operator =(const sprite_flipbook&) = delete;
};



__end_ns_td
