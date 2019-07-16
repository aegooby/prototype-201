
#pragma	once
#include	"__common.hpp"
#include	"component.hpp"
#include	"entity.hpp"
#include	<unordered_map>

__begin_ns_td

class	component_manager
{
public:
	virtual ~component_manager() = default;
	virtual std::unique_ptr<component>&	component(entity&) = 0;
	virtual void	add_component(entity&, std::unique_ptr<class component>&&) = 0;
	virtual void	remove_component(entity&) = 0;
};

template	<typename component_type>
class	component_manager_template : public component_manager
{
public:
	using component_t = component_type;
	using index_t = size_t;
	std::vector<std::unique_ptr<class component>>	components;
protected:
	std::unordered_map<id_t, index_t>	__entity_map;
public:
	virtual ~component_manager_template() = default;
	virtual std::unique_ptr<class component>&	component(entity& entity)
	{
		if (!__entity_map.count(entity.id()))
			throw std::runtime_error("Entity does not have requested component");
		return components.at(__entity_map.at(entity.id()));
	}
	virtual void	add_component(entity& entity, std::unique_ptr<class component>&& component)
	{
		if (__entity_map.count(entity.id()))
			throw std::runtime_error("Duplicate component");
		__entity_map.at(entity.id()) = components.size();
		components.emplace_back(std::forward<std::unique_ptr<class component>>(component));
	}
	virtual void	remove_component(entity& entity)
	{
		components.erase(components.begin() + __entity_map.at(entity.id()));
		__entity_map.erase(entity.id());
	}
};

class	render_manager : public component_manager_template<render_component>
{
public:
	virtual ~render_manager() = default;
};
class	transform_manager : public component_manager_template<transform_component>
{
public:
	virtual ~transform_manager() = default;
};
class	collision_manager : public component_manager_template<collision_component>
{
public:
	virtual ~collision_manager() = default;
};
class	input_manager : public component_manager_template<input_component>
{
public:
	virtual ~input_manager() = default;
};

__end_ns_td
