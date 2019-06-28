
#pragma	once
#include	"__common.hpp"
#include	"renderer.hpp"
#include	<vector>

__begin_ns_td

class	sprite_base
{
protected:
	const std::string	__name;
public:
	sprite_base(const std::string& name) : __name(name) {  }
	inline __attribute__((always_inline))
	virtual const std::string&	name() const
	{
		return __name;
	}
	virtual ~sprite_base() = 0;
	virtual void	create(td::renderer&, const std::string&) = 0;
	virtual void	render(td::renderer&, render_component&) = 0;
};

class	sprite : public sprite_base
{
public:
	using __base = sprite_base;
protected:
	SDL_Texture*		__texture = nullptr;
public:
	sprite(const std::string& name) : __base(name) {  }
	sprite(sprite&& other) : __base(other.__name), __texture(other.__texture)
	{
		other.__texture = nullptr;
	}
	sprite&	operator =(sprite&& other)
	{
		__texture = other.__texture;
		other.__texture = nullptr;
		return *this;
	}
	virtual ~sprite()
	{
		if (__texture)
		{
			SDL_DestroyTexture(__texture);
			__texture = nullptr;
		}
	}
	virtual void	create(td::renderer&, const std::string&) override;
	virtual void	render(td::renderer&, render_component&) override;
	
	// Preventing copying
	sprite(const sprite& other) = delete;
	sprite&	operator =(const sprite&) = delete;
};

class	sprite_flipbook : public sprite_base
{
public:
	using __base = sprite_base;
protected:
	std::vector<sprite>			__sprites;
	std::vector<std::string>	__paths;
	float		__fps = 0;
	uint32_t	__framec = 0;
	uint32_t	__index = 0;
public:
	sprite_flipbook(const std::string& name, float fps = 0.0f) : __base(name), __fps(fps)
	{
		if (__fps <= 0 || __fps > float(global::game_fps))
			throw std::runtime_error(std::string("Invalid fps, flipbook: ") + __name);
	}
	virtual ~sprite_flipbook() = default;
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
	size_t	frames() const
	{
		return __sprites.size();
	}
	inline __attribute__((always_inline))
	float	seconds() const
	{
		return 1.0f / __fps * frames();
	}
	void	create(td::renderer&, const std::string&) override;
	void	render(td::renderer&, render_component&) override;
};



__end_ns_td
