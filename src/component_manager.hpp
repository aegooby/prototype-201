
#pragma once
#include "__common.hpp"
#include "component.hpp"
#include "exception.hpp"

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
    std::unordered_map<id_t, index_t> __entity_map;

public:
    virtual ~component_manager();
    std::unique_ptr<struct component>& component(entity&);
    /** @brief Registers a component under the specified entity. */
    void add_component(entity&, std::unique_ptr<struct component>&&);
    /** @brief Removes the component associated with the manager's type. */
    void remove_component(entity&);
};

inline component_manager::~component_manager() { }

template<typename component_type>
class component_manager_template : public component_manager
{
public:
    using component_t = component_type;

    virtual ~component_manager_template() = default;
};

class render_manager : public component_manager_template<render_component>
{
public:
    virtual ~render_manager() = default;
};
class transform_manager : public component_manager_template<transform_component>
{
public:
    virtual ~transform_manager() = default;
};
class movement_manager : public component_manager_template<transform_component>
{
public:
    virtual ~movement_manager() = default;
};
class collision_manager : public component_manager_template<collision_component>
{
public:
    virtual ~collision_manager() = default;
};
class input_manager : public component_manager_template<input_component>
{
public:
    virtual ~input_manager() = default;
};

} // namespace p201
