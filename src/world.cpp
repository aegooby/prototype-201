
#include "world.hpp"

#include "__common.hpp"
#include "component.hpp"
#include "entity_manager.hpp"
#include "input_system.hpp"
#include "movement_system.hpp"
#include "render_system.hpp"
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
    component_managers.emplace(typeid(render_component),
                               std::make_unique<render_manager>());
    component_managers.emplace(typeid(transform_component),
                               std::make_unique<transform_manager>());
    component_managers.emplace(typeid(collision_component),
                               std::make_unique<collision_manager>());
    component_managers.emplace(typeid(movement_component),
                               std::make_unique<movement_manager>());
    component_managers.emplace(typeid(input_component),
                               std::make_unique<input_manager>());

    systems.emplace(typeid(render_system),
                    std::make_unique<render_system>(*this));
    systems.emplace(typeid(movement_system),
                    std::make_unique<movement_system>(*this));
    systems.emplace(typeid(input_system),
                    std::make_unique<input_system>(*this));
}

entity& world::new_entity()
{
    return entity_manager.new_entity(*this);
}
entity& world::new_entity(const std::string& name)
{
    entity& entity = new_entity();
    serializer.load_entity(name, entity);
    return entity;
}
void world::delete_entity(id_t id, const std::string& name)
{
    auto& entity = *entity_manager.entities.at(id);
    serializer.save_entity(name, entity);
    delete_entity(id);
}
void world::delete_entity(id_t id)
{
    auto& entity = *entity_manager.entities.at(id);
    for (auto& manager : component_managers)
    {
        auto& mgr = *manager.second;
        mgr.remove_component(entity);
    }
    for (auto& system : systems)
    {
        auto& sys = *system.second;
        sys.deregister_entity(entity);
    }
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
        auto& sys = *system.second;
        if ((sys.flag & entity.flag ^ sys.flag).none())
            sys.register_entity(entity);
    }
}
void world::remove_component(class entity&   entity,
                             std::type_index component_type)
{
    component_managers.at(component_type)->remove_component(entity);
    for (auto& system : systems)
    {
        auto& sys = *system.second;
        if (sys.flag.test(system::flags.at(component_type)))
        {
            sys.deregister_entity(entity);
        }
    }
}

} // namespace p201
