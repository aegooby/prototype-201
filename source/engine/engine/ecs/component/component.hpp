
#pragma once

#include "../../__common.hpp"
#include "../entity.hpp"

#include <pugixml.hpp>

namespace p201
{
struct component
{
    static constexpr std::size_t flag = 0;

    entity::id_t entity;

    component(entity::id_t entity);
    virtual ~component() = 0;

    /** @brief Saves a component into XML. */
    virtual pugi::xml_node serialize() = 0;
    /** @brief Reads a component from XML. */
    virtual void deserialize(const pugi::xml_node&) = 0;

    component(const component&) = delete;
    component(component&&)      = delete;
    component& operator=(const component&) = delete;
    component& operator=(component&&) = delete;
};
template<std::size_t flag>
struct flag_component
{
    using type = void;
};
template<std::size_t flag>
using flag_component_t = typename flag_component<flag>::type;
} // namespace p201
