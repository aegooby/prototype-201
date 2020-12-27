
#pragma once
#include "__common.hpp"
#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "event.hpp"
#include "event_bus.hpp"
#include "xml_serializer.hpp"

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
    event_bus event_bus;
    /** @brief State storage for inputs. */
    class keyboard& keyboard;
    class mouse&    mouse;
    /** @brief Used for loading and saving entities to XML. */
    xml_serializer serializer;

protected:
    entity_manager entity_manager;

protected:
    std::unique_ptr<system>& __system(std::type_index);

public:
    world(class keyboard&, class mouse&);
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
                       std::type_index);
    void remove_component(class entity&, std::type_index);
};

} // namespace p201
