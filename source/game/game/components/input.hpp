
#pragma once
#include <engine/__common.hpp>
#include <engine/ecs.hpp>

namespace p201
{
namespace components
{
struct input : public component
{
    using __base  = component;
    using manager = component_manager_template<components::input>;

    static constexpr std::size_t flag = 5;

    input(entity::id_t entity) : __base(entity) { }
    virtual ~input() override = default;

    /** @brief Saves a component into XML. */
    virtual pugi::xml_node serialize() override
    {
        auto node = pugi::xml_node();
        node.set_name("component");
        node.append_attribute("flag").set_value(flag);
        node.append_attribute("name").set_value("input");

        return node;
    }
    /** @brief Reads a component from XML. */
    virtual void deserialize(const pugi::xml_node&) override { }
};
} // namespace components
} // namespace p201