
#include "entity.hpp"

#include "__common.hpp"
#include "world.hpp"

namespace p201
{

entity::entity(const id_t id, class world& world) : world(world), id(id) { }
bool entity::operator==(const entity& other)
{
    return id == other.id;
}
std::unique_ptr<component>& entity::__component(std::type_index component_type)
{
    return world.component(*this, component_type);
}
void entity::__add_component(std::unique_ptr<struct component>&& component,
                             std::type_index                     component_type)
{
    using ptr_t = std::unique_ptr<struct component>;
    world.add_component(*this, std::forward<ptr_t>(component), component_type);
}
void entity::__remove_component(std::type_index component_type)
{
    world.remove_component(*this, component_type);
}

} // namespace p201
