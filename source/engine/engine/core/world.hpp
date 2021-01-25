
#pragma once
#include "../asset.hpp"
#include "../ecs.hpp"
#include "../event.hpp"
#include "../physx.hpp"
#include "../ui.hpp"

#include <__common.hpp>
#include <typeindex>
#include <unordered_map>

namespace p201
{

class world
{
public:
    /* CONTEXT OBJECTS */
    /** @brief Contains SDL window and window data. */
    class window& window;
    /** @brief State storage for keyboard inputs. */
    class keyboard& keyboard;
    /** @brief State storage for mouse inputs. */
    class mouse& mouse;

    /* PHYSX */
    /** @brief Scene used to manage PhysX actors. */
    px::scene scene;

    /* GLOBAL OBJECTS */
    /** @brief Table of systems (type of system is the key). */
    std::unordered_map<std::type_index, std::unique_ptr<system>> systems;
    /** @brief Handles events and forwards them to the relevant systems. */
    events::manager event_manager;
    /** @brief Used for loading and saving entities to XML. */
    serialize::xml serializer;
    /** @brief Read the name idiot. */
    ui::hud hud;
    /** @brief Contains sprites. */
    assets::textures::manager sprite_manager;

protected:
    using cmptr_t = std::unique_ptr<components::manager>;
    /* INTERNAL OBJECTS */
    /** @brief It's in the name retard. */
    entities::manager entity_manager;
    /** @brief Table of component managers (type of component is the key). */
    std::unordered_map<std::type_index, cmptr_t> component_managers;

    std::unique_ptr<system>& __system(std::type_index);

public:
    world(class window&, class keyboard&, class mouse&);
    ~world() = default;
    entity& new_entity();
    void    delete_entity(entity::id_t);
    template<typename system_type>
    system_type& system()
    {
        return *static_cast<system_type*>(__system(typeid(system_type)).get());
    }
    std::unique_ptr<struct component>& component(entity::id_t, std::type_index);
    void    add_component(entity::id_t, std::unique_ptr<struct component>&&,
                          std::type_index, std::size_t);
    void    remove_component(entity::id_t, std::type_index, std::size_t);
    entity& entity(entity::id_t id);

    template<typename type>
    void create_component()
    {
        using mgr_t = typename type::manager;
        component_managers.emplace(typeid(type), std::make_unique<mgr_t>());
    }
    template<typename type>
    void create_system()
    {
        systems.emplace(typeid(type), std::make_unique<type>(*this));
    }
};

} // namespace p201
