
#include	"__common.hpp"
#include	"world.hpp"
#include	"entity_manager.hpp"
#include	"system.hpp"
#include	"render_system.hpp"
#include	"physics_system.hpp"
#include	"input_system.hpp"

__begin_ns_td

std::unique_ptr<system>&	world::__system(std::type_index system_type)
{
	return systems.at(system_type);
}
world::world(class keyboard& keyboard, class mouse& mouse) : event_bus(*this), keyboard(keyboard), mouse(mouse)
{
	component_managers.emplace(typeid(render_component), std::make_unique<render_manager>());
	component_managers.emplace(typeid(transform_component), std::make_unique<transform_manager>());
	component_managers.emplace(typeid(collision_component), std::make_unique<collision_manager>());
	component_managers.emplace(typeid(input_component), std::make_unique<input_manager>());
	component_managers.emplace(typeid(state_component), std::make_unique<state_manager>());
	
	systems.emplace(typeid(render_system), std::make_unique<render_system>(*this));
	systems.emplace(typeid(physics_system), std::make_unique<physics_system>(*this));
	systems.emplace(typeid(input_system), std::make_unique<input_system>(*this));
}

entity&	world::new_entity(entity_type type)
{
	return entity_manager.new_entity(type, *this);
}
void	world::delete_entity(id_t id)
{
	auto&	entity = *entity_manager.entities.at(id);
	for (auto& manager : component_managers)
	{
		auto&	mgr = *manager.second;
		mgr.remove_component(entity);
	}
	for (auto& system : systems)
	{
		auto&	sys = *system.second;
		sys.deregister_entity(entity);
	}
	entity_manager.delete_entity(id);
}

std::unique_ptr<class component>&	world::component(class entity& entity, std::type_index component_type)
{
	return component_managers.at(component_type)->component(entity);
}
void	world::add_component(class entity& entity, std::unique_ptr<class component>&& component, std::type_index component_type)
{
	component_managers.at(component_type)->add_component(entity, std::forward<std::unique_ptr<class component>>(component));
	entity.flag.set(system::flags.at(component_type));
	for (auto& system : systems)
	{
		auto&	sys = *system.second;
		if ((sys.flag & entity.flag) == sys.flag)
		{
			sys.register_entity(entity);
		}
	}
}
void	world::remove_component(class entity& entity, std::type_index component_type)
{
	component_managers.at(component_type)->remove_component(entity);
	for (auto& system : systems)
	{
		auto&	sys = *system.second;
		if (sys.flag.test(system::flags.at(component_type)))
		{
			sys.deregister_entity(entity);
		}
	}
}

__end_ns_td
