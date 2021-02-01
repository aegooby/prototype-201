
#pragma once
#include <engine/__common.hpp>
#include <engine/ecs.hpp>

namespace p201
{
namespace components
{
struct physics : public component
{
    using __base  = component;
    using manager = component_manager_template<components::physics>;

    static constexpr std::size_t flag = 3;

    enum shape_types : std::uint8_t
    {
        undefined = 0,
        capsule   = 1,
        box       = 2,
    };

    float       sf         = 0.0f;
    float       df         = 0.0f;
    float       e          = 0.0f;
    float       density    = 0.0f;
    bool        dynamic    = true;
    shape_types shape_type = undefined;
    union shape_params
    {
        struct
        {
            float r;
            float hh;
        } capsule;
        struct
        {
            float hx;
            float hy;
            float hz;
        } box;
        shape_params()  = default;
        ~shape_params() = default;
    } shape_param;

    px::rigid_actor* actor = nullptr;
    px::shape*       shape = nullptr;

    physics(entity::id_t entity) : __base(entity) { }
    virtual ~physics() override = default;

    /** @brief Saves a component into XML. */
    virtual pugi::xml_node serialize() override
    {
        auto node = pugi::xml_node();
        node.set_name("component");
        node.append_attribute("flag").set_value(flag);
        node.append_attribute("name").set_value("physics");

        auto material_node = node.append_child("material");
        material_node.append_attribute("sf").set_value(sf);
        material_node.append_attribute("df").set_value(df);
        material_node.append_attribute("e").set_value(e);
        material_node.append_attribute("density").set_value(density);

        auto shape_node = node.append_child("shape");
        shape_node.append_attribute("dynamic").set_value(dynamic);
        shape_node.append_attribute("type").set_value(shape_type);
        switch (shape_type)
        {
            case shape_types::capsule:
            {
                auto& capsule      = shape_param.capsule;
                auto  capsule_node = shape_node.append_child("capsule");
                capsule_node.append_attribute("r").set_value(capsule.r);
                capsule_node.append_attribute("hh").set_value(capsule.hh);
                break;
            }
            case shape_types::box:
            {
                auto& box      = shape_param.box;
                auto  box_node = shape_node.append_child("box");
                box_node.append_attribute("hx").set_value(box.hx);
                box_node.append_attribute("hy").set_value(box.hy);
                box_node.append_attribute("hz").set_value(box.hz);
                break;
            }
            default:
                break;
        }

        return node;
    }
    /** @brief Reads a component from XML. */
    virtual void deserialize(const pugi::xml_node& node) override
    {
        auto material_node = node.child("material");
        sf                 = material_node.attribute("sf").as_float();
        df                 = material_node.attribute("df").as_float();
        e                  = material_node.attribute("e").as_float();
        density            = material_node.attribute("density").as_float();

        auto shape_node = node.child("shape");
        dynamic         = shape_node.attribute("dynamic").as_bool();
        shape_type      = shape_types(shape_node.attribute("type").as_uint());
        switch (shape_type)
        {
            case shape_types::capsule:
            {
                auto& capsule      = shape_param.capsule;
                auto  capsule_node = shape_node.child("capsule");
                capsule.r          = capsule_node.attribute("r").as_float();
                capsule.hh         = capsule_node.attribute("hh").as_float();
                break;
            }
            case shape_types::box:
            {
                auto& box      = shape_param.box;
                auto  box_node = shape_node.child("box");
                box.hx         = box_node.attribute("hx").as_float();
                box.hy         = box_node.attribute("hy").as_float();
                box.hz         = box_node.attribute("hz").as_float();
                break;
            }
            default:
                break;
        }
    }
};
} // namespace components
} // namespace p201