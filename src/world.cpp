
#include "world.hpp"

#include "__common.hpp"
#include "component.hpp"
#include "entity_manager.hpp"
#include "system.hpp"
#include "util.hpp"

namespace p201
{

std::unique_ptr<system>& world::__system(std::type_index system_type)
{
    return systems.at(system_type);
}
world::world(class window& window, class keyboard& keyboard, class mouse& mouse)
    : window(window), keyboard(keyboard), mouse(mouse), event_bus(*this)
{
    component_managers.emplace(typeid(components::render),
                               std::make_unique<managers::render>());
    component_managers.emplace(typeid(components::transform),
                               std::make_unique<managers::transform>());
    component_managers.emplace(typeid(components::collision),
                               std::make_unique<managers::collision>());
    component_managers.emplace(typeid(components::movement),
                               std::make_unique<managers::movement>());
    component_managers.emplace(typeid(components::input),
                               std::make_unique<managers::input>());
    component_managers.emplace(typeid(components::animation),
                               std::make_unique<managers::animation>());
    component_managers.emplace(typeid(components::camera),
                               std::make_unique<managers::camera>());

    systems.emplace(typeid(systems::render),
                    std::make_unique<systems::render>(*this));
    systems.emplace(typeid(systems::movement),
                    std::make_unique<systems::movement>(*this));
    systems.emplace(typeid(systems::collision),
                    std::make_unique<systems::collision>(*this));
    systems.emplace(typeid(systems::input),
                    std::make_unique<systems::input>(*this));
    systems.emplace(typeid(systems::animation),
                    std::make_unique<systems::animation>(*this));
    systems.emplace(typeid(systems::camera),
                    std::make_unique<systems::camera>(*this));
}

entity& world::new_entity()
{
    return entity_manager.new_entity(*this);
}
void world::delete_entity(std::size_t id)
{
    auto& entity = *entity_manager.entities.at(id);
    for (auto& manager : component_managers)
        manager.second->remove_component(entity);
    for (auto& system : systems) system.second->deregister_entity(entity);
    entity_manager.delete_entity(id);
}

std::unique_ptr<struct component>&
world::component(class entity& entity, std::type_index component_type)
{
    return component_managers.at(component_type)->component(entity);
}
void world::add_component(class entity&                       entity,
                          std::unique_ptr<struct component>&& component,
                          std::type_index component_type, std::size_t flag)
{
    using ptr_t = std::unique_ptr<struct component>;
    component_managers.at(component_type)
        ->add_component(entity, std::forward<ptr_t>(component));
    entity.flag.set(flag);
    for (auto& system : systems)
    {
        if ((system.second->flag & entity.flag ^ system.second->flag).none())
            system.second->register_entity(entity);
    }
}
void world::remove_component(class entity&   entity,
                             std::type_index component_type, std::size_t flag)
{
    component_managers.at(component_type)->remove_component(entity);
    for (auto& system : systems)
    {
        if (system.second->flag.test(flag))
            system.second->deregister_entity(entity);
    }
}
entity& world::entity(std::size_t id)
{
    return *entity_manager.entities.at(id);
}

} // namespace p201
