
#pragma once
#include <__common.hpp>
#include <engine/ecs.hpp>

namespace p201
{
namespace components
{
struct health : public component
{
    using __base  = component;
    using manager = component_manager_template<components::health>;

    static constexpr std::size_t flag = 8;

    float current_hp     = 0.0f;
    float max_hp         = 0.0f;
    float current_shield = 0.0f;
    float max_shield     = 0.0f;

    health(entity::id_t entity) : __base(entity) { }
    virtual ~health() override = default;

    /** @brief Saves a component into XML. */
    virtual pugi::xml_node serialize() override
    {
        auto node = pugi::xml_node();
        node.set_name("component");
        node.append_attribute("flag").set_value(flag);
        node.append_attribute("name").set_value("health");

        auto hp_node = node.append_child("hp");
        hp_node.append_attribute("current").set_value(current_hp);
        hp_node.append_attribute("max").set_value(max_hp);

        auto shield_node = node.append_child("shield");
        shield_node.append_attribute("current").set_value(current_shield);
        shield_node.append_attribute("max").set_value(max_shield);

        return node;
    }
    /** @brief Reads a component from XML. */
    virtual void deserialize(const pugi::xml_node& node) override
    {
        auto hp_node = node.child("hp");
        current_hp   = hp_node.attribute("current").as_float();
        max_hp       = hp_node.attribute("max").as_float();

        auto shield_node = node.child("shield");
        current_shield   = shield_node.attribute("current").as_float();
        max_shield       = shield_node.attribute("max").as_float();
    }
};
} // namespace components
} // namespace p201