
#pragma	once
#include	"__common.hpp"
#include	<vector>
#include	<string>

__begin_ns_td

class	component
{
public:
	component() = default;
	virtual ~component() = 0;
};

class	render_component : public component
{
protected:
	struct	color
	{
		uint8_t	r, g, b, a;
	};
	SDL_Rect	__rect;
	color		__color;
	bool		__ready = false;
public:
	render_component() = default;
	virtual ~render_component() = default;
	virtual void	render(td::renderer& renderer)
	{
		if (!__ready)
			return;
	}
};

class	sprite_component : public render_component
{
protected:
	SDL_Surface*	__surface = nullptr;
	SDL_Texture*	__texture = nullptr;
	std::vector<std::string>	__sprites;
public:
	sprite_component() = default;
	virtual ~sprite_component();
	void	load(td::renderer& renderer);
	virtual void	render(td::renderer& renderer) override;
};


class	physics_component : public component
{
public:
	physics_component() = default;
	virtual ~physics_component() = default;
};

// Unfinished
class	audio_component : public component
{
public:
	audio_component() = default;
	virtual ~audio_component() = default;
};

class	input_component : public component
{
public:
	input_component() = default;
	virtual ~input_component() = default;
};

__end_ns_td
