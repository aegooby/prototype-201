
#include	"__common.hpp"
#include	"world.hpp"

__begin_ns_td

std::unique_ptr<class component>&	world::component(class entity& entity, std::type_index component_type)
{
	return managers.at(component_type)->component(entity);
}
void	world::add_component(class entity& entity, std::unique_ptr<class component>&& component, std::type_index component_type)
{
	managers.at(component_type)->add_component(entity, std::forward<std::unique_ptr<class component>>(component));
}
void	world::remove_component(class entity& entity, std::type_index component_type)
{
	managers.at(component_type)->remove_component(entity);
}

__end_ns_td
