
#pragma once

#include "../../__common.hpp"

#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace p201
{

struct component;

/**
 * @brief Entities are an id, flag, and type they shouldn't have shit else.
 *        They don't actually store components they just forward them to the
 *        world which forwards them to the component managers.
 */
class entity
{
protected:
    /* CONTEXT OBJECTS */
    class world& world;
    /* HELPER FUNCTIONS */
    [[nodiscard]] std::unique_ptr<component>& __component(std::type_index);
    void __add_component(std::unique_ptr<struct component>&&, std::type_index,
                         std::size_t);
    void __remove_component(std::type_index, std::size_t);

public:
    using id_t = std::size_t;

    static constexpr std::size_t flag_bits = 32;
    /** @brief Stores flag for all components in the entity. */
    std::bitset<flag_bits> flag;
    /** @brief Used to access entity in the manager. */
    const id_t id;

    entity(const std::size_t, class world&);
    ~entity() = default;
    template<typename component_type>
    [[nodiscard]] component_type& component();
    template<typename component_type>
    component_type& add_component();
    template<typename component_type>
    void remove_component();
    bool operator==(const entity&);

    entity(const entity&) = delete;
    entity(entity&&)      = delete;
    entity& operator=(const entity&) = delete;
    entity& operator=(entity&&) = delete;
};

} // namespace p201
