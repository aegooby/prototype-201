
#pragma once
#include <engine/__common.hpp>
#include <engine/ecs.hpp>
#include <engine/util.hpp>

namespace p201
{
namespace components
{
struct transform : public component
{
    using __base  = component;
    using manager = component_manager_template<components::transform>;

    static constexpr std::size_t flag = 2;

    /** @brief Previous coordinate used to interpolate in updates. */
    vector_3 lerp = vector_3(0.0f, 0.0f, 0.0f);
    /** @brief Game coordinate position (not isometric position). */
    vector_3 position = vector_3(0.0f, 0.0f, 0.0f);
    /** @brief Direction the entity is facing (not always used). */
    enum directions : std::uint8_t
    {
        north      = 1,
        south      = 2,
        east       = 3,
        west       = 4,
        north_east = 5,
        north_west = 6,
        south_east = 7,
        south_west = 8,
    } direction = north;

    transform(entity::id_t entity) : __base(entity) { }
    virtual ~transform() override = default;

    /** @brief Saves a component into XML. */
    virtual pugi::xml_node serialize() override
    {
        auto node = pugi::xml_node();
        node.set_name("component");
        node.append_attribute("flag").set_value(flag);
        node.append_attribute("name").set_value("transform");

        auto position_node = node.append_child("position");
        position_node.append_attribute("x").set_value(position.x);
        position_node.append_attribute("y").set_value(position.y);
        position_node.append_attribute("z").set_value(position.z);

        auto direction_node = node.append_child("direction");
        direction_node.append_attribute("value").set_value(direction);

        return node;
    }
    /** @brief Reads a component from XML. */
    virtual void deserialize(const pugi::xml_node& node) override
    {
        auto position_node = node.child("position");
        position.x         = position_node.attribute("x").as_float();
        position.y         = position_node.attribute("y").as_float();
        position.z         = position_node.attribute("z").as_float();

        lerp = position;

        auto direction_node = node.child("direction");
        direction = directions(direction_node.attribute("value").as_uint());
    }
};
} // namespace components
} // namespace p201