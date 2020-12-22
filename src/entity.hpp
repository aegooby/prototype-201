
#pragma once
#include "__common.hpp"
#include "component.hpp"
#include "system.hpp"

#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace p201
{

using id_t = size_t;

enum class entity_type
{
    player,
};

/**
 * @brief Entities are an id, flag, and type they shouldn't have shit else.
 *        They don't actually store components they just forward them to the
 *        world which forwards them to the component managers.
 */
class entity
{
public:
    class world&           world;
    std::bitset<flag_bits> flag;

public:
    const id_t        id;
    const entity_type type;

protected:
    std::unique_ptr<component>& __component(std::type_index);
    void __add_component(std::unique_ptr<struct component>&&, std::type_index);
    void __remove_component(std::type_index);

public:
    entity(const id_t, const entity_type, class world&);
    virtual ~entity() = default;
    template<typename component_type>
    component_type& component()
    {
        return *static_cast<component_type*>(
            __component(typeid(component_type)).get());
    }
    template<typename component_type, typename... types>
    void add_component(types&&... args)
    {
        __add_component(std::make_unique<component_type>(
                            *this, std::forward<types>(args)...),
                        typeid(component_type));
    }
    template<typename component_type>
    void remove_component()
    {
        __remove_component(typeid(component_type));
    }
    bool operator==(const entity&);

    // Preventing copying and moving
    entity(const entity&) = delete;
    entity(entity&&)      = delete;
    entity& operator=(const entity&) = delete;
    entity& operator=(entity&&) = delete;
};

} // namespace p201
