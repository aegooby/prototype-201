
#pragma once
#include "../__common.hpp"
#include "../exception.hpp"
#include "component.hpp"

#include <unordered_map>

namespace p201
{

/**
 * @brief Component managers are responsible for adding and removing components
 *        to & from entities. That's all they do bitch.
 */
class component_manager
{
public:
    using index_t = std::size_t;
    std::vector<std::unique_ptr<component>> components;

protected:
    std::unordered_map<std::size_t, index_t> __entity_map;

public:
    virtual ~component_manager();
    std::unique_ptr<struct component>& component(entity&);
    /** @brief Registers a component under the specified entity. */
    void add_component(entity&, std::unique_ptr<struct component>&&);
    /** @brief Removes the component associated with the manager's type. */
    void remove_component(entity&);
};

inline component_manager::~component_manager() = default;

template<typename component_type>
class component_manager_template : public component_manager
{
public:
    using component_t = component_type;

    virtual ~component_manager_template() = default;
};

namespace managers
{
using render       = component_manager_template<components::render>;
using transform    = component_manager_template<components::transform>;
using physics      = component_manager_template<components::physics>;
using character    = component_manager_template<components::character>;
using input        = component_manager_template<components::input>;
using animation    = component_manager_template<components::animation>;
using camera_focus = component_manager_template<components::camera_focus>;
using health       = component_manager_template<components::health>;
using hud          = component_manager_template<components::hud>;
} // namespace managers
} // namespace p201
