
#pragma once
#include "__common.hpp"
#include "component.hpp"

#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace p201
{

/**
 * @brief Entities are an id, flag, and type they shouldn't have shit else.
 *        They don't actually store components they just forward them to the
 *        world which forwards them to the component managers.
 */
class entity
{
protected:
    class world&                world;
    std::unique_ptr<component>& __component(std::type_index);
    void __add_component(std::unique_ptr<struct component>&&, std::type_index,
                         std::size_t);
    void __remove_component(std::type_index, std::size_t);

public:
    std::bitset<component::flag_bits> flag;
    const std::size_t                        id;

    entity(const std::size_t, class world&);
    virtual ~entity() = default;
    template<typename component_type>
    component_type& component()
    {
        return *static_cast<component_type*>(
            __component(typeid(component_type)).get());
    }
    template<typename component_type>
    component_type& add_component()
    {
        __add_component(std::make_unique<component_type>(*this),
                        typeid(component_type), component_type::flag);
        return component<component_type>();
    }
    template<typename component_type>
    void remove_component()
    {
        __remove_component(typeid(component_type), component_type::flag);
    }
    bool operator==(const entity&);

    // Preventing copying and moving
    entity(const entity&) = delete;
    entity(entity&&)      = delete;
    entity& operator=(const entity&) = delete;
    entity& operator=(entity&&) = delete;
};

} // namespace p201
