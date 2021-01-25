
#include "world.hpp"

#include "engine.hpp"

#include <__common.hpp>
#include <ecs.hpp>
#include <util.hpp>

namespace p201
{

std::unique_ptr<system>& world::__system(std::type_index system_type)
{
    return systems.at(system_type);
}
world::world(class window& window, class keyboard& keyboard, class mouse& mouse)
    : window(window),
      keyboard(keyboard),
      mouse(mouse),
      scene(*this, px::sdk),
      event_manager(*this),
      serializer(*this),
      sprite_manager("assets/sprites")
{ }

entity& world::new_entity()
{
    return entity_manager.new_entity(*this);
}
void world::delete_entity(entity::id_t id)
{
    for (auto& manager : component_managers)
        manager.second->remove_component(id);
    for (auto& system : systems) system.second->deregister_entity(id);
    entity_manager.delete_entity(id);
}

entity& world::entity(entity::id_t id)
{
    return *entity_manager.entities.at(id);
}

std::unique_ptr<struct component>&
world::component(entity::id_t id, std::type_index component_type)
{
    return component_managers.at(component_type)->component(id);
}
void world::add_component(entity::id_t                        id,
                          std::unique_ptr<struct component>&& component,
                          std::type_index component_type, std::size_t flag)
{
    using ptr_t = std::unique_ptr<struct component>;
    component_managers.at(component_type)
        ->add_component(id, std::forward<ptr_t>(component));
    auto& entity = this->entity(id);
    entity.flag.set(flag);
    for (auto& system : systems)
    {
        if ((system.second->flag & entity.flag ^ system.second->flag).none())
            system.second->register_entity(id);
    }
}
void world::remove_component(entity::id_t id, std::type_index component_type,
                             std::size_t flag)
{
    component_managers.at(component_type)->remove_component(id);
    for (auto& system : systems)
    {
        if (system.second->flag.test(flag))
            system.second->deregister_entity(id);
    }
}

} // namespace p201
