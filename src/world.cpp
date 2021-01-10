
#include "world.hpp"

#include "__common.hpp"
#include "component.hpp"
#include "engine.hpp"
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
    : window(window),
      keyboard(keyboard),
      mouse(mouse),
      scene(engine::sdk),
      controller_manager(scene),
      event_manager(*this),
      serializer(*this),
      sprite_manager("assets/sprites")
{

    component_managers.emplace(typeid(components::render),
                               std::make_unique<managers::render>());
    component_managers.emplace(typeid(components::transform),
                               std::make_unique<managers::transform>());
    component_managers.emplace(typeid(components::character),
                               std::make_unique<managers::character>());
    component_managers.emplace(typeid(components::physics),
                               std::make_unique<managers::physics>());
    component_managers.emplace(typeid(components::input),
                               std::make_unique<managers::input>());
    component_managers.emplace(typeid(components::animation),
                               std::make_unique<managers::animation>());
    component_managers.emplace(typeid(components::camera_focus),
                               std::make_unique<managers::camera_focus>());
    component_managers.emplace(typeid(components::health),
                               std::make_unique<managers::health>());
    component_managers.emplace(typeid(components::hud),
                               std::make_unique<managers::hud>());

    systems.emplace(typeid(systems::render),
                    std::make_unique<systems::render>(*this));
    systems.emplace(typeid(systems::physics),
                    std::make_unique<systems::physics>(*this));
    systems.emplace(typeid(systems::input),
                    std::make_unique<systems::input>(*this));
    systems.emplace(typeid(systems::animation),
                    std::make_unique<systems::animation>(*this));
    systems.emplace(typeid(systems::combat),
                    std::make_unique<systems::combat>(*this));
}

entity& world::new_entity()
{
    return entity_manager.new_entity(*this);
}
void world::delete_entity(std::size_t id)
{
    for (auto& manager : component_managers)
        manager.second->remove_component(id);
    for (auto& system : systems) system.second->deregister_entity(id);
    entity_manager.delete_entity(id);
}

entity& world::entity(std::size_t id)
{
    return *entity_manager.entities.at(id);
}

std::unique_ptr<struct component>&
world::component(std::size_t id, std::type_index component_type)
{
    return component_managers.at(component_type)->component(id);
}
void world::add_component(std::size_t                         id,
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
void world::remove_component(std::size_t id, std::type_index component_type,
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
