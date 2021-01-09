
#include "serialize.hpp"

#include "__common.hpp"
#include "system.hpp"
#include "world.hpp"

namespace p201
{
namespace serialize
{
xml::xml(class world& world) : world(world) { }
void xml::load_entity(class entity& entity, const std::string& name)
{
    std::filesystem::path       filepath = (directory / name).concat(".xml");
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
                auto& render      = entity.add_component<components::render>();
                render.family     = component.get<std::string>("family");
                render.visible    = component.get<bool>("visible");
                render.iso        = component.get<bool>("iso");
                render.camera     = component.get<bool>("camera");
                render.rect.w     = component.get<float>("rect.w");
                render.rect.h     = component.get<float>("rect.h");
                render.srcrect.w  = render.rect.w;
                render.srcrect.h  = render.rect.h;
                render.offset.x() = component.get<float>("offset.x");
                render.offset.y() = component.get<float>("offset.y");
                break;
            }
            case components::transform::flag:
            {
                auto& transform = entity.add_component<components::transform>();
                transform.position.x() = component.get<float>("position.x");
                transform.position.y() = component.get<float>("position.y");
                transform.position.z() = component.get<float>("position.z");
                transform.lerp         = transform.position;
                break;
            }
            case components::physics::flag:
            {
                auto& physics   = entity.add_component<components::physics>();
                physics.dynamic = component.get<bool>("dynamic");
                physics.sf      = component.get<float>("sf");
                physics.df      = component.get<float>("df");
                physics.e       = component.get<float>("e");
                physics.density = component.get<float>("density");
                break;
            }
            case components::character::flag:
            {
                auto& character = entity.add_component<components::character>();
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
                auto& animation = entity.add_component<components::animation>();
                animation.fps   = component.get<float>("fps");
                break;
            }
            case components::camera_focus::flag:
            {
                auto& camera = entity.add_component<components::camera_focus>();
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
    /* PhysX */
    if (entity.flag.test(components::physics::flag))
    {
        auto& physics = entity.component<components::physics>();
        if (entity.flag.test(components::character::flag))
        {
            auto& character = entity.component<components::character>();
            character.init(world.controller_manager, physics);
            physics.actor = character.controller->getActor();
        }
        else
            physics.init(world.scene);
        if (entity.flag.test(components::transform::flag))
        {
            auto& transform   = entity.component<components::transform>();
            auto px_transform = physx::PxTransform(convert(transform.position));
            physics.actor->setGlobalPose(px_transform);
        }
    }
}
} // namespace serialize
} // namespace p201
