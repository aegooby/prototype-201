
#include	"__common.hpp"
#include	"entity.hpp"
#include	"world.hpp"

__begin_ns_td

entity::entity(const id_t id, const std::string& name, class world& world) : world(world), __id(id), __name(name) {  }
const id_t	entity::id() const
{
	return __id;
}
bool	entity::operator ==(const entity& other)
{
	return __id == other.__id;
}
std::unique_ptr<component>&	entity::__component(std::type_index component_type)
{
	return world.component(*this, component_type);
}
void	entity::__add_component(std::unique_ptr<class component>&& component, std::type_index component_type)
{
	world.add_component(*this, std::forward<std::unique_ptr<class component>>(component), component_type);
}
void	entity::__remove_component(std::type_index component_type)
{
	world.remove_component(*this, component_type);
}

__end_ns_td

