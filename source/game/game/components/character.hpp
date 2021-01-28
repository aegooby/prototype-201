
#pragma once
#include <__common.hpp>
#include <engine/ecs.hpp>
#include <engine/physx.hpp>
#include <engine/util.hpp>
#include <forge/math.hpp>

namespace p201
{
namespace components
{
struct character : public component
{
    using __base  = component;
    using manager = component_manager_template<components::character>;

    static constexpr std::size_t flag = 4;

    px::controller* controller = nullptr;
    px::shape*      shape      = nullptr;

    vector_3 accel     = vector_3(0.0f, 0.0f, 0.0f);
    vector_3 velocity  = vector_3(0.0f, 0.0f, 0.0f);
    float    max_speed = 0.0f;
    float    friction  = 0.0f;

    character(entity::id_t entity) : __base(entity) { }
    virtual ~character() override = default;

    /** @brief Saves a component into XML. */
    virtual pugi::xml_node serialize() override
    {
        auto node = pugi::xml_node();
        node.set_name("component");
        node.append_attribute("flag").set_value(flag);
        node.append_attribute("name").set_value("character");

        auto physics_node = node.append_child("physics");
        physics_node.append_attribute("max_speed").set_value(max_speed);
        physics_node.append_attribute("friction").set_value(friction);

        return node;
    }
    /** @brief Reads a component from XML. */
    virtual void deserialize(const pugi::xml_node& node) override
    {
        auto physics_node = node.child("physics");
        max_speed         = physics_node.attribute("max_speed").as_float();
        friction          = physics_node.attribute("friction").as_float();
    }
};
} // namespace components
} // namespace p201