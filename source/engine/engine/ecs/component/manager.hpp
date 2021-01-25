
#pragma once
#include "../entity.hpp"
#include "component.hpp"

#include <__common.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

namespace p201
{

namespace components
{
/**
 * @brief Component managers are responsible for adding and removing components
 *        to & from entities. That's all they do bitch.
 */
class manager
{
public:
    using index_t = std::size_t;
    std::vector<std::unique_ptr<component>> components;

protected:
    std::unordered_map<entity::id_t, index_t> __entity_map;

public:
    virtual ~manager();
    [[nodiscard]] std::unique_ptr<struct component>& component(entity::id_t);
    /** @brief Registers a component under the specified entity. */
    void add_component(entity::id_t, std::unique_ptr<struct component>&&);
    /** @brief Removes the component associated with the manager's type. */
    void remove_component(entity::id_t);
};

inline manager::~manager() = default;
} // namespace components

template<typename component_type>
class component_manager_template : public components::manager
{
public:
    using component_t = component_type;

    virtual ~component_manager_template() override = default;
};
} // namespace p201
