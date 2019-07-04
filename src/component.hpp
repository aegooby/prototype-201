
#pragma	once
#include	"__common.hpp"
#include	"sprite.hpp"
#include	"key.hpp"
#include	<map>
#include	<unordered_map>
#include	<vector>
#include	<string>

__begin_ns_td

class	component
{
public:
	td::entity&	entity;
protected:
	const std::string	__id;
public:
	component(td::entity& entity) : entity(entity), __id(std::string("0x") + std::to_string(long(this))) {  }
	component(td::entity& entity, const std::string& id) : entity(entity), __id(id) {  }
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
	render_component(td::entity& entity) : __base(entity) {  }
	render_component(td::entity& entity, const std::string& id) : __base(entity, id) {  }
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
	physics_component(td::entity& entity) : __base(entity) {  }
	physics_component(td::entity& entity, const std::string& id) : __base(entity, id) {  }
	virtual ~physics_component() = default;
};

// TODO: finish
class	audio_component : public component
{
public:
	using __base = component;
public:
	audio_component(td::entity& entity) : __base(entity) {  }
	audio_component(td::entity& entity, const std::string& id) : __base(entity, id) {  }
	virtual ~audio_component() = default;
};

class	input_component : public component
{
public:
	using __base = component;
protected:
	std::map<action, std::pair<keycode, modifier>>		__key_mappings;
	std::map<action, std::pair<mousecode, modifier>>	__mouse_mappings;
public:
	input_component(td::entity& entity) : __base(entity) {  }
	input_component(td::entity& entity, const std::string& id) : __base(entity, id) {  }
	virtual ~input_component() = default;
	inline __attribute__((always_inline))
	const std::map<action, std::pair<keycode, modifier>>&	key_mappings() const
	{
		return __key_mappings;
	}
	inline __attribute__((always_inline))
	const std::map<action, std::pair<mousecode, modifier>>&	mouse_mappings() const
	{
		return __mouse_mappings;
	}
	void	map(action, keycode, modifier);
	void	map(action, mousecode, modifier);
	void	read(const td::keyboard&, const td::mouse&);
};

__end_ns_td
