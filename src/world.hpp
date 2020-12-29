
#pragma once
#include "__common.hpp"
#include "camera.hpp"
#include "component.hpp"
#include "entity_manager.hpp"
#include "event.hpp"
#include "event_bus.hpp"
#include "serialize.hpp"
#include "quadtree.hpp"

#include <typeindex>
#include <unordered_map>

namespace p201
{

class world
{
public:
    using cmptr_t = std::unique_ptr<component_manager>;
    /** @brief Table of component managers (type of component is the key). */
    std::unordered_map<std::type_index, cmptr_t> component_managers;
    /** @brief Table of systems (type of system is the key). */
    std::unordered_map<std::type_index, std::unique_ptr<system>> systems;
    /** @brief Handles events and forwards them to the relevant systems. */
    event_bus     event_bus;
    class window& window;
    /** @brief State storage for keyboard inputs. */
    class keyboard& keyboard;
    /** @brief State storage for mouse inputs. */
    class mouse& mouse;
    /** @brief Used for loading and saving entities to XML. */
    serialize::xml serializer;
    /** @brief Used for loading sprites. */
    sprite::manager sprite_manager;
    /** @brief Used to apply camera transform. */
    camera camera;
    
    class quadtree quadtree;
    //this is a quadtree

protected:
    entity_manager entity_manager;

    std::unique_ptr<system>& __system(std::type_index);

public:
    world(class window&, class keyboard&, class mouse&);
    ~world() = default;
    entity& new_entity();
    void    delete_entity(id_t);
    template<typename system_type>
    system_type& system()
    {
        return *static_cast<system_type*>(__system(typeid(system_type)).get());
    }
    std::unique_ptr<struct component>& component(class entity&,
                                                 std::type_index);
    void add_component(class entity&, std::unique_ptr<struct component>&&,
                       std::type_index, std::size_t);
    void remove_component(class entity&, std::type_index, std::size_t);
};

} // namespace p201
