
#pragma once
#include "__common.hpp"
#include "asset.hpp"
#include "camera.hpp"
#include "component.hpp"
#include "entity_manager.hpp"
#include "event.hpp"
#include "physx.hpp"
#include "serialize.hpp"
#include "ui.hpp"

#include <typeindex>
#include <unordered_map>

namespace p201
{

class world
{
public:
    /*** CONTEXT OBJECTS ***/
    /** @brief Contains SDL window and window data. */
    class window& window;
    /** @brief State storage for keyboard inputs. */
    class keyboard& keyboard;
    /** @brief State storage for mouse inputs. */
    class mouse& mouse;

    /*** PHYSX ***/
    /** @brief Scene used to manage PhysX actors. */
    /** @todo Might need to be moved */
    px::scene scene;

    /*** GLOBAL OBJECTS ***/
    /** @brief Table of systems (type of system is the key). */
    std::unordered_map<std::type_index, std::unique_ptr<system>> systems;
    /** @brief Handles events and forwards them to the relevant systems. */
    events::manager event_manager;
    /** @brief Used for loading and saving entities to XML. */
    serialize::xml serializer;
    /** @brief Read the name idiot. */
    ui::hud hud;
    /** @brief Contains sprites (and one day, sound files). */
    assets::sprite::manager sprite_manager;

protected:
    using cmptr_t = std::unique_ptr<component_manager>;
    /*** INTERNAL OBJECTS ***/
    /** @brief It's in the name retard. */
    entity_manager entity_manager;
    /** @brief Table of component managers (type of component is the key). */
    std::unordered_map<std::type_index, cmptr_t> component_managers;

    std::unique_ptr<system>& __system(std::type_index);

public:
    world(class window&, class keyboard&, class mouse&);
    ~world() = default;
    entity& new_entity();
    void    delete_entity(std::size_t);
    template<typename system_type>
    system_type& system()
    {
        return *static_cast<system_type*>(__system(typeid(system_type)).get());
    }
    std::unique_ptr<struct component>& component(class entity&,
                                                 std::type_index);
    void    add_component(class entity&, std::unique_ptr<struct component>&&,
                          std::type_index, std::size_t);
    void    remove_component(class entity&, std::type_index, std::size_t);
    entity& entity(std::size_t id);
};

} // namespace p201
