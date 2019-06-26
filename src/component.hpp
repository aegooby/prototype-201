
#pragma	once
#include	"__common.hpp"
#include	<unordered_map>
#include	<vector>
#include	<string>

__begin_ns_td

class	component
{
public:
	component() = default;
	virtual ~component() = 0;
};

class	render_component
{
private:
	std::unordered_map<std::string, std::unique_ptr<sprite_base>>	__children;
protected:
	struct	color
	{
		uint8_t	r, g, b, a;
	};
	SDL_Rect	__rect;
	color		__color;
public:
	render_component() = default;
	virtual ~render_component() = default;
	virtual void	render(td::renderer&);
	inline __attribute__((always_inline))
	const SDL_Rect&	rect() const
	{
		return __rect;
	}
	inline __attribute__((always_inline))
	void	rect(const SDL_Rect& rect)
	{
		__rect = rect;
	}
	inline __attribute__((always_inline))
	SDL_Rect*	rect_addr()
	{
		return &__rect;
	}
	inline __attribute__((always_inline))
	std::unordered_map<std::string, std::unique_ptr<sprite_base>>&	children()
	{
		return __children;
	}
	inline __attribute__((always_inline))
	const std::unordered_map<std::string, std::unique_ptr<sprite_base>>&	children() const
	{
		return __children;
	}
	void	add_child(std::unique_ptr<sprite_base>&&);
	void	remove_child(const std::string&);
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
