
#pragma	once
#include	"__common.hpp"
#include	"sprite.hpp"
#include	<unordered_map>
#include	<vector>
#include	<string>

__begin_ns_td

class	component
{
protected:
	const std::string	__id;
public:
	component() : __id(std::to_string(long(this))) {  }
	component(const std::string& id) : __id(id) {  }
	virtual ~component() = 0;
	inline __attribute__((always_inline))
	const std::string&	id() const
	{
		return __id;
	}
};

class	render_component : public component
{
public:
	using __base = component;
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
	render_component(const std::string& id) : __base(id) {  }
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
	void	rect(int x, int y, int w, int h)
	{
		__rect = { x, y, w, h };
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
	using __base = component;
public:
	physics_component() = default;
	physics_component(const std::string& id) : __base(id) {  }
	virtual ~physics_component() = default;
};

// TODO: finish
class	audio_component : public component
{
public:
	using __base = component;
public:
	audio_component() = default;
	audio_component(const std::string& id) : __base(id) {  }
	virtual ~audio_component() = default;
};

class	input_component : public component
{
public:
	using __base = component;
public:
	input_component() = default;
	input_component(const std::string& id) : __base(id) {  }
	virtual ~input_component() = default;
};

__end_ns_td
