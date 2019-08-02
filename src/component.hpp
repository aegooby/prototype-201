
#pragma	once
#include	"__common.hpp"
#include	"sprite.hpp"
#include	"vector.hpp"
#include	"point.hpp"
#include	"ecs_common.hpp"
#include	"hitbox.hpp"
#include	"key.hpp"
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
	void	add_flipbook(const std::string&, float, const sprite_info&);
	void	remove_flipbook(const std::string& name);
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
	float		max_speed = 10.0f;
public:
	transform_component(class entity& entity) : __base(entity) {  }
	virtual ~transform_component() = default;
};

class	collision_component : public physics_component
{
public:
	using __base = physics_component;
public:
	capsule	hitbox;
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
	std::map<state, std::pair<std::unique_ptr<key>, modifier>>	key_mappings;
	std::map<state, std::pair<mousecode, modifier>>				mouse_mappings;
public:
	input_component(class entity& entity) : __base(entity)
	{
		key_mappings.emplace(state::up, std::make_pair(std::make_unique<single_key>(keycode::W), modifier::NONE));
		key_mappings.emplace(state::down, std::make_pair(std::make_unique<single_key>(keycode::S), modifier::NONE));
		key_mappings.emplace(state::left, std::make_pair(std::make_unique<single_key>(keycode::A), modifier::NONE));
		key_mappings.emplace(state::right, std::make_pair(std::make_unique<single_key>(keycode::D), modifier::NONE));
		key_mappings.emplace(state::up_right, std::make_pair(std::make_unique<multi_key>(keycode::W, keycode::D), modifier::NONE));
		key_mappings.emplace(state::up_left, std::make_pair(std::make_unique<multi_key>(keycode::W, keycode::A), modifier::NONE));
		key_mappings.emplace(state::down_right, std::make_pair(std::make_unique<multi_key>(keycode::S, keycode::D), modifier::NONE));
		key_mappings.emplace(state::down_left, std::make_pair(std::make_unique<multi_key>(keycode::S, keycode::A), modifier::NONE));
	}
	virtual ~input_component() = default;
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
