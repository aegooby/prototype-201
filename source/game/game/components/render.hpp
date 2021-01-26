
#pragma once
#include <__common.hpp>
#include <engine/ecs.hpp>
#include <engine/media-layer.hpp>

namespace p201
{
namespace components
{
struct render : public component
{
    using __base  = component;
    using manager = component_manager_template<components::render>;

    static constexpr std::size_t flag = 1;

    /** @brief Whether or not to display the sprite on rendering. */
    bool visible = true;
    /** @brief Whether to transform the rendering to isometric. */
    bool iso = true;
    /** @brief Whether to camera transform the sprite. */
    bool camera = true;
    /** @brief Family of flipbooks associated with this component. */
    std::string family = "unknown";
    /** @brief Floating point rect that textures are rendered onto. */
    SDL_FRect rect = { .x = 0.0f, .y = 0.0f, .w = 0.0f, .h = 0.0f };
    /** @brief Portion of source rectangle to be rendered. */
    SDL_Rect srcrect = { .x = 0, .y = 0, .w = 0, .h = 0 };
    /** @brief Texture rendered onto rect. */
    SDL_Texture* texture = nullptr;
    /** @brief The displacement factor of the sprite from its center point. */
    vector_2 offset = vector_2(0.0f, 0.0f);

    render(entity::id_t entity) : __base(entity) { }
    virtual ~render() override = default;

    /** @brief Saves a component into XML. */
    virtual pugi::xml_node serialize() override
    {
        auto node = pugi::xml_node();
        node.set_name("component");
        node.append_attribute("flag").set_value(flag);
        node.append_attribute("name").set_value("render");

        auto flags_node = node.append_child("flags");
        flags_node.append_attribute("visible").set_value(visible);
        flags_node.append_attribute("iso").set_value(iso);
        flags_node.append_attribute("camera").set_value(camera);

        auto family_node = node.append_child("family");
        family_node.append_attribute("value").set_value(family.c_str());

        auto rect_node = node.append_child("rect");
        rect_node.append_attribute("w").set_value(rect.w);
        rect_node.append_attribute("h").set_value(rect.h);

        auto offset_node = node.append_child("offset");
        offset_node.append_attribute("x").set_value(offset.x);
        offset_node.append_attribute("y").set_value(offset.y);

        return node;
    }
    /** @brief Reads a component from XML. */
    virtual void deserialize(const pugi::xml_node& node) override
    {
        auto flags_node = node.child("flags");
        visible         = flags_node.attribute("visible").as_bool();
        iso             = flags_node.attribute("iso").as_bool();
        camera          = flags_node.attribute("camera").as_bool();

        auto family_node = node.child("family");
        family           = family_node.attribute("value").value();

        auto rect_node = node.child("rect");
        rect.w         = rect_node.attribute("w").as_float();
        rect.h         = rect_node.attribute("h").as_float();

        srcrect.w = rect.w;
        srcrect.h = rect.h;

        auto offset_node = node.child("offset");
        offset.x         = offset_node.attribute("x").as_float();
        offset.y         = offset_node.attribute("y").as_float();
    }
};
} // namespace components
} // namespace p201