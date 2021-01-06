
#pragma once
#include "__common.hpp"
#include "component.hpp"
#include "entity.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <filesystem>

namespace p201
{
namespace serialize
{
class xml
{
public:
    std::filesystem::path directory;

    xml()  = default;
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
                    /** @todo This is fucked */
                    auto& physics = entity.add_component<components::physics>();
                    physics.velocity.x() = component.get<float>("velocity.x");
                    physics.velocity.y() = component.get<float>("velocity.y");
                    physics.velocity.z() = component.get<float>("velocity.z");
                    physics.mass         = component.get<float>("mass");
                    break;
                }
                case components::collision::flag:
                {
                    auto& collision =
                        entity.add_component<components::collision>();
                    auto flag = component.get<std::size_t>("hitbox.flag");
                    switch (flag)
                    {
                        case hitboxes::circle::flag:
                        {
                            collision.hitbox =
                                std::make_unique<hitboxes::circle>();
                            auto circle = dynamic_cast<hitboxes::circle*>(
                                collision.hitbox.get());
                            circle->radius =
                                component.get<float>("hitbox.radius");
                            break;
                        }
                        case hitboxes::square::flag:
                        {
                            collision.hitbox =
                                std::make_unique<hitboxes::square>();
                            auto square = dynamic_cast<hitboxes::square*>(
                                collision.hitbox.get());
                            square->width =
                                component.get<float>("hitbox.width");
                            square->height =
                                component.get<float>("hitbox.height");
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }
                case components::input::flag:
                {
                    auto& input = entity.add_component<components::input>();
                    input.force = component.get<float>("force");
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
