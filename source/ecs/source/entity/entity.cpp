
#include "entity.hpp"

#include "../component.hpp"

#include <__common.hpp>
#include <core.hpp>

namespace p201
{

entity::entity(const id_t id, class world& world) : world(world), id(id) { }
bool entity::operator==(const entity& other)
{
    return id == other.id;
}
std::unique_ptr<component>& entity::__component(std::type_index component_type)
{
    return world.component(id, component_type);
}
void entity::__add_component(std::unique_ptr<struct component>&& component,
                             std::type_index component_type, std::size_t flag)
{
    using ptr_t = std::unique_ptr<struct component>;
    world.add_component(id, std::forward<ptr_t>(component), component_type,
                        flag);
}
void entity::__remove_component(std::type_index component_type,
                                std::size_t     flag)
{
    world.remove_component(id, component_type, flag);
}

} // namespace p201
