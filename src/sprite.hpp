
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
	SDL_Texture*		__texture;
	std::string			__file;
public:
	sprite(const std::string& name) : __base(name) {  }
	virtual ~sprite()
	{
		if (__texture)
			SDL_DestroyTexture(__texture);
	}
	virtual void	create(td::renderer&, const std::string&) override;
	virtual void	render(td::renderer&, render_component&) override;
};

class	sprite_flipbook : public sprite_base
{
public:
	using __base = sprite_base;
protected:
	std::vector<sprite>			__sprites;
	std::vector<std::string>	__paths;
	uint32_t	__frame_delay = 0;
	uint32_t	__framec = 0;
	uint32_t	__index = 0;
public:
	sprite_flipbook(const std::string& name) : __base(name) {  }
	virtual ~sprite_flipbook() = default;
	inline __attribute__((always_inline))
	void	frame_delay(uint32_t frame_delay)
	{
		__frame_delay = frame_delay;
	}
	inline __attribute__((always_inline))
	uint32_t	frame_delay() const
	{
		return __frame_delay;
	}
	void	create(td::renderer&, const std::string&) override;
	void	render(td::renderer&, render_component&) override;
};



__end_ns_td
