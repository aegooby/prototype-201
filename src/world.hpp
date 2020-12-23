
#pragma once
#include "__common.hpp"
#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "event.hpp"
#include "event_bus.hpp"

#include <typeindex>
#include <unordered_map>

namespace p201
{

class world
{
public:
    std::unordered_map<std::type_index, std::unique_ptr<component_manager>>
        component_managers;
    std::unordered_map<std::type_index, std::unique_ptr<system>> systems;
    event_bus                                                    event_bus;
    class keyboard&                                              keyboard;
    class mouse&                                                 mouse;

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
