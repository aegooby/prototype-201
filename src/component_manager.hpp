
#pragma	once
#include	"__common.hpp"
#include	"component.hpp"
#include	"entity.hpp"

__begin_ns_td

template	<typename component_type>
class	component_manager
{
public:
	std::vector<std::shared_ptr<component>>	components;
public:
	template	<typename ... types>
	void	add_component(entity& entity, types&& ... args)
	{
		components.emplace_back(std::make_shared<component_type>(entity, std::forward<types>(args)...));
		entity.add_component(components.back());
	}
	void	remove_component(std::shared_ptr<component_type>& component)
	{
		components.erase(std::remove_if(components.begin(), components.end(), [&component](std::shared_ptr<component_type>& __component)
										{
											return &component == &__component;
										}));
	}
};

class	render_manager : public component_manager<render_component> {  };
class	transform_manager : public component_manager<transform_component> {  };
class	collision_manager : public component_manager<collision_component> {  };

__end_ns_td
