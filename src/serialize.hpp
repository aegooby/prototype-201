
#pragma once
#include "__common.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "physx.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <filesystem>

namespace p201
{
namespace serialize
{
class xml
{
private:
    /** @todo This ain't it chief */
    px::scene& scene;

public:
    std::filesystem::path directory;

    xml(px::scene& scene) : scene(scene) { }
    ~xml() = default;
    void load_entity(class entity& entity, const std::string& name)
    {
        std::filesystem::path filepath = (directory / name).concat(".xml");
        boost::property_tree::ptree ptree;
        boost::property_tree::read_xml(filepath.string(), ptree);

        for (auto& component_pair : ptree.get_child("entity.components"))
        {
            const auto& component = component_pair.second;
            const auto& flag      = component.get<std::size_t>("flag");
            switch (flag)
            {
                case components::render::flag:
                {
                    auto& render   = entity.add_component<components::render>();
                    render.family  = component.get<std::string>("family");
                    render.visible = component.get<bool>("visible");
                    render.iso     = component.get<bool>("iso");
                    render.camera  = component.get<bool>("camera");
                    render.rect.w  = component.get<float>("rect.w");
                    render.rect.h  = component.get<float>("rect.h");
                    render.srcrect.w  = render.rect.w;
                    render.srcrect.h  = render.rect.h;
                    render.offset.x() = component.get<float>("offset.x");
                    render.offset.y() = component.get<float>("offset.y");
                    break;
                }
                case components::transform::flag:
                {
                    auto& transform =
                        entity.add_component<components::transform>();
                    transform.position.x() = component.get<float>("position.x");
                    transform.position.y() = component.get<float>("position.y");
                    transform.position.z() = component.get<float>("position.z");
                    transform.lerp         = transform.position;
                    break;
                }
                case components::physics::flag:
                {
                    auto& physics = entity.add_component<components::physics>();
                    /** @todo Add switch for box types */
                    /** @todo Add switch for dynamic/static */
                    bool  dynamic = component.get<bool>("dynamic");
                    float sf      = component.get<float>("sf");
                    float df      = component.get<float>("df");
                    float e       = component.get<float>("e");
                    break;
                }
                case components::character::flag:
                {
                    auto& character =
                        entity.add_component<components::character>();
                    (void)character;
                    break;
                }
                case components::input::flag:
                {
                    auto& input = entity.add_component<components::input>();
                    (void)input;
                    break;
                }
                case components::animation::flag:
                {
                    auto& animation =
                        entity.add_component<components::animation>();
                    animation.fps = component.get<float>("fps");
                    break;
                }
                case components::camera_focus::flag:
                {
                    auto& camera =
                        entity.add_component<components::camera_focus>();
                    (void)camera;
                    break;
                }
                case components::health::flag:
                {
                    auto& health  = entity.add_component<components::health>();
                    health.hp     = component.get<float>("hp");
                    health.max_hp = component.get<float>("max_hp");
                    break;
                }
                case components::hud::flag:
                {
                    auto& hud = entity.add_component<components::hud>();
                    (void)hud;
                    break;
                }
                default:
                    break;
            }
        }
        if (entity.flag.test(components::transform::flag) &&
            entity.flag.test(components::physics::flag))
        {
            auto& transform = entity.component<components::transform>();
            auto& physics   = entity.component<components::physics>();
            auto  pxt       = physx::PxTransform(convert(transform.position));
            physics.actor->setGlobalPose(pxt);
        }
    }
    void save_entity(class entity& entity, const std::string& name)
    {
        std::filesystem::path filepath = (directory / name).concat(".xml");
        boost::property_tree::ptree ptree;
        ptree.put("entity.name", name);
        ptree.put("entity.components", "");

        for (std::size_t i = 0; i < entity.flag.size(); ++i)
        {
            if (!entity.flag.test(i)) continue;
            auto& component = ptree.add("entity.components.component", "");
            component.add("flag", i);
            switch (i)
            {
                default:
                    break;
            }
        }

        boost::property_tree::write_xml(filepath.string(), ptree);
    }
};
} // namespace serialize
} // namespace p201
