
#pragma	once
#include	"__common.hpp"
#include	"sprite.hpp"
#include	"vector.hpp"
#include	"ecs_common.hpp"
#include	<map>
#include	<unordered_map>
#include	<vector>
#include	<string>

__begin_ns_td

class	component
{
public:
	class entity&	entity;
public:
	component(class entity& entity) : entity(entity) {  }
	virtual ~component() = 0;
	
	// Preventing copying and moving
	component(const component&) = delete;
	component(component&&) = delete;
	component&	operator =(const component&) = delete;
	component&	operator =(component&&) = delete;
};

class	render_component : public component
{
public:
	using __base = component;
public:
	std::unordered_map<std::string, sprite_flipbook>	flipbooks;
	SDL_Rect	rect;
	std::string	name = "idle";
public:
	render_component(class entity& entity) : __base(entity) {  }
	virtual ~render_component() = default;
	template	<typename ... types>
	void	add_flipbook(const std::string& name, types&& ... args)
	{
		flipbooks.emplace(name, sprite_flipbook(name, std::forward<types>(args)...));
	}
	void	remove_flipbook(const std::string& name)
	{
		flipbooks.erase(name);
	}
};


class	physics_component : public component
{
public:
	using __base = component;
public:
	physics_component(class entity& entity) : __base(entity) {  }
	virtual ~physics_component() = default;
};

class	transform_component : public physics_component
{
public:
	using __base = physics_component;
public:
	vector_3	position;
	vector_3	velocity;
	vector_3	acceleration;
public:
	transform_component(class entity& entity) : __base(entity) {  }
	virtual ~transform_component() = default;
};

class	collision_component : public physics_component
{
public:
	using __base = physics_component;
public:
	
public:
	collision_component(class entity& entity) : __base(entity) {  }
	virtual ~collision_component() = default;
};

// TODO: finish
class	audio_component : public component
{
public:
	using __base = component;
public:
	audio_component(class entity& entity) : __base(entity) {  }
	virtual ~audio_component() = default;
};

class	input_component : public component
{
public:
	using __base = component;
public:
	std::map<state, std::pair<keycode, modifier>>		key_mappings;
	std::map<state, std::pair<mousecode, modifier>>	mouse_mappings;
public:
	input_component(class entity& entity) : __base(entity) {  }
	virtual ~input_component() = default;
	void	add_mapping(state, keycode, modifier);
	void	add_mapping(state, mousecode, modifier);
	void	remove_mapping(state);
};

class	state_component : public component
{
public:
	using __base = component;
	enum state	state = state::idle;
public:
	state_component(class entity& entity) : __base(entity) {  }
	virtual ~state_component() = default;
};

__end_ns_td
