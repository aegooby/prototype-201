
#pragma once
#include "entity.hpp"
#include "../component.hpp"

namespace p201
{
template<typename component_type>
[[nodiscard]] component_type& entity::component()
{
    return *static_cast<component_type*>(
        __component(typeid(component_type)).get());
}
template<typename component_type>
component_type& entity::add_component()
{
    __add_component(std::make_unique<component_type>(id),
                    typeid(component_type), component_type::flag);
    return component<component_type>();
}
template<typename component_type>
void entity::remove_component()
{
    __remove_component(typeid(component_type), component_type::flag);
}
} // namespace p201