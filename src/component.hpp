
#pragma	once
#include	"__common.hpp"
#include	"sprite.hpp"
#include	"key.hpp"
#include	"vector.hpp"
#include	<map>
#include	<unordered_map>
#include	<vector>
#include	<string>

__begin_ns_td

template	<typename component_type>
class	component_manager
{
public:
	std::vector<std::shared_ptr<component_type>>	components;
public:
	template	<typename ... types>
	void	add_component(types&& ... args)
	{
		components.emplace_back(std::make_shared<component_type>(std::forward<types>(args)...));
	}
	void	remove_component(std::shared_ptr<component_type>& component)
	{
		components.erase(std::remove_if(components.begin(), components.end(0), [&component](std::shared_ptr<component_type>& __component)
										{
											return &component == &__component;
										}));
	}
};

class	render_manager : public component_manager<render_component> {  };
class	transform_manager : public component_manager<transform_component> {  };

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
public:
	std::unordered_map<std::string, sprite_flipbook>	flipbooks;
	SDL_Rect	rect = { 100, 100, 100, 74 };
public:
	render_component(td::entity& entity) : __base(entity) {  }
	render_component(td::entity& entity, const std::string& id) : __base(entity, id) {  }
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
	physics_component(td::entity& entity) : __base(entity) {  }
	physics_component(td::entity& entity, const std::string& id) : __base(entity, id) {  }
	virtual ~physics_component() = default;
};

class	transform_component : public physics_component
{
public:
	using __base = physics_component;
public:
	float	x, y, z;
public:
	transform_component(td::entity& entity) : __base(entity) {  }
	transform_component(td::entity& entity, const std::string& id) : __base(entity, id) {  }
	virtual ~transform_component() = default;
};

class	movement_component : public physics_component
{
public:
	using __base = physics_component;
public:
	vector_3	velocity;
	vector_3	acceleration;
public:
	movement_component(td::entity& entity) : __base(entity) {  }
	movement_component(td::entity& entity, const std::string& id) : __base(entity, id) {  }
	virtual ~movement_component() = default;
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
public:
	std::map<action, std::pair<keycode, modifier>>		key_mappings;
	std::map<action, std::pair<mousecode, modifier>>	mouse_mappings;
public:
	input_component(td::entity& entity) : __base(entity) {  }
	input_component(td::entity& entity, const std::string& id) : __base(entity, id) {  }
	virtual ~input_component() = default;
	void	add_mapping(action, keycode, modifier);
	void	add_mapping(action, mousecode, modifier);
	void	remove_mapping(action);
};

__end_ns_td
