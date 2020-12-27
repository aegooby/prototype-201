
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
world::world(class keyboard& keyboard, class mouse& mouse)
    : event_bus(*this), keyboard(keyboard), mouse(mouse)
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

    systems.emplace(typeid(systems::render),
                    std::make_unique<systems::render>(*this));
    systems.emplace(typeid(systems::movement),
                    std::make_unique<systems::movement>(*this));
    systems.emplace(typeid(systems::input),
                    std::make_unique<systems::input>(*this));
}

entity& world::new_entity()
{
    debug(std::cout << "new entity(id: " << entity_manager.entityc() << ")");
    debug(std::cout << std::endl);
    return entity_manager.new_entity(*this);
}
void world::delete_entity(id_t id)
{
    auto& entity = *entity_manager.entities.at(id);
    debug(std::cout << "delete entity(id: " << id << ")" << std::endl);
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
                          std::type_index                     component_type)
{
    using ptr_t = std::unique_ptr<struct component>;
    component_managers.at(component_type)
        ->add_component(entity, std::forward<ptr_t>(component));
    entity.flag.set(system::flags.at(component_type));
    for (auto& system : systems)
    {
        if ((system.second->flag & entity.flag ^ system.second->flag).none())
            system.second->register_entity(entity);
    }
}
void world::remove_component(class entity&   entity,
                             std::type_index component_type)
{
    component_managers.at(component_type)->remove_component(entity);
    for (auto& system : systems)
    {
        if (system.second->flag.test(system::flags.at(component_type)))
            system.second->deregister_entity(entity);
    }
}

} // namespace p201
