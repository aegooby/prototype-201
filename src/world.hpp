
#pragma	once
#include	"__common.hpp"
#include	"component_manager.hpp"
#include	<unordered_map>
#include	<typeindex>

__begin_ns_td

class	world
{
public:
	std::unordered_map<std::type_index, std::unique_ptr<component_manager>>	managers;
protected:
	
public:
	world()
	{
		managers.emplace(typeid(render_component), std::make_unique<render_manager>());
		managers.emplace(typeid(transform_component), std::make_unique<transform_manager>());
		managers.emplace(typeid(collision_component), std::make_unique<collision_manager>());
		managers.emplace(typeid(input_component), std::make_unique<input_manager>());
	}
	std::unique_ptr<class component>&	component(class entity&, std::type_index);
	void	add_component(class entity&, std::unique_ptr<class component>&&, std::type_index);
	void	remove_component(class entity&, std::type_index);
};

__end_ns_td
