
#pragma once
#include "character.hpp"

#include <__common.hpp>
#include <engine/ecs.hpp>

namespace p201
{
namespace components
{
struct attack : public component
{
    using __base  = component;
    using manager = component_manager_template<components::attack>;

    static constexpr std::size_t flag = 9;

    px::shape* shape = nullptr;

    attack(entity::id_t entity) : __base(entity) { }
    virtual ~attack() override = default;

    /** @brief Saves a component into XML. */
    virtual pugi::xml_node serialize() override
    {
        auto node = pugi::xml_node();
        node.set_name("component");
        node.append_attribute("flag").set_value(flag);
        node.append_attribute("name").set_value("attack");

        return node;
    }
    /** @brief Reads a component from XML. */
    virtual void deserialize(const pugi::xml_node&) override { }
};
} // namespace components
} // namespace p201