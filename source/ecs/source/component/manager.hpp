
#pragma once
#include "component.hpp"

#include <__common.hpp>
#include <memory>
#include <unordered_map>
#include <util.hpp>
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
    std::unordered_map<std::size_t, index_t> __entity_map;

public:
    virtual ~manager();
    std::unique_ptr<struct component>& component(std::size_t);
    /** @brief Registers a component under the specified entity. */
    void add_component(std::size_t, std::unique_ptr<struct component>&&);
    /** @brief Removes the component associated with the manager's type. */
    void remove_component(std::size_t);
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
