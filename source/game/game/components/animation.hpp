
#pragma once
#include <__common.hpp>
#include <engine/ecs.hpp>

namespace p201
{
namespace components
{
struct animation : public component
{
    using __base  = component;
    using manager = component_manager_template<components::animation>;

    static constexpr std::size_t flag = 6;

    std::string name      = "default";
    std::size_t frame     = 0;
    std::size_t index     = 0;
    float       fps       = 0.0f;
    bool        interrupt = false;
    bool        loop      = true;

    animation(entity::id_t entity) : __base(entity) { }
    virtual ~animation() override = default;

    /** @brief Saves a component into XML. */
    virtual pugi::xml_node serialize() override
    {
        auto node = pugi::xml_node();
        node.set_name("component");
        node.append_attribute("flag").set_value(flag);
        node.append_attribute("name").set_value("animation");

        auto fps_node = node.append_child("fps");
        fps_node.append_attribute("value").set_value(fps);

        return node;
    }
    /** @brief Reads a component from XML. */
    virtual void deserialize(const pugi::xml_node& node) override
    {
        auto fps_node = node.child("fps");
        fps           = fps_node.attribute("value").as_float();
    }
};
} // namespace components
template<>
struct flag_component<components::animation::flag>
{
    using type = components::animation;
};
} // namespace p201