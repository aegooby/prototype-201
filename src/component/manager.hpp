
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

namespace managers
{

    class render : public component_manager_template<components::render>
    {
    public:
        virtual ~render() = default;
    };
    class transform : public component_manager_template<components::transform>
    {
    public:
        virtual ~transform() = default;
    };
    class movement : public component_manager_template<components::movement>
    {
    public:
        virtual ~movement() = default;
    };
    class collision : public component_manager_template<components::collision>
    {
    public:
        virtual ~collision() = default;
    };
    class input : public component_manager_template<components::input>
    {
    public:
        virtual ~input() = default;
    };
    class animation : public component_manager_template<components::animation>
    {
    public:
        virtual ~animation() = default;
    };
} // namespace managers
} // namespace p201
