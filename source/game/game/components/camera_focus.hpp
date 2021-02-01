
#pragma once
#include <engine/__common.hpp>
#include <engine/ecs.hpp>

namespace p201
{
namespace components
{
struct camera_focus : public component
{
    using __base  = component;
    using manager = component_manager_template<components::camera_focus>;

    static constexpr std::size_t flag = 7;

    camera_focus(entity::id_t entity) : __base(entity) { }
    virtual ~camera_focus() override = default;

    /** @brief Saves a component into XML. */
    virtual pugi::xml_node serialize() override
    {
        auto node = pugi::xml_node();
        node.set_name("component");
        node.append_attribute("flag").set_value(flag);
        node.append_attribute("name").set_value("camera_focus");

        return node;
    }
    /** @brief Reads a component from XML. */
    virtual void deserialize(const pugi::xml_node&) override { }
};
} // namespace components
} // namespace p201