
#include "character.hpp"

#include <__common.hpp>

namespace p201
{
namespace systems
{
float character::direction_angle(const components::transform& transform)
{
    switch (transform.direction)
    {
        case components::transform::north:
            return px::PxPiDivFour * 7.0f;
            break;
        case components::transform::south:
            return px::PxPiDivFour * 3.0f;
            break;
        case components::transform::east:
            return px::PxPiDivFour * 1.0f;
            break;
        case components::transform::west:
            return px::PxPiDivFour * 5.0f;
            break;
        case components::transform::north_east:
            return px::PxPiDivFour * 0.0f;
            break;
        case components::transform::north_west:
            return px::PxPiDivFour * 6.0f;
            break;
        case components::transform::south_east:
            return px::PxPiDivFour * 2.0f;
            break;
        case components::transform::south_west:
            return px::PxPiDivFour * 4.0f;
            break;
        default:
            throw std::runtime_error("Invalid direction");
            break;
    }
}

void character::start() { }
void character::update(float dt)
{
    __base::update(dt);
    for (auto& id : __registered_entities)
    {
        auto& entity    = world.entity(id);
        auto& transform = entity.component<components::transform>();
        auto& physics   = entity.component<components::physics>();
        auto& character = entity.component<components::character>();
        // character.velocity += character.accel * dt;

        character.controller->move(convert(character.velocity * dt), 0.1f, dt,
                                   px::PxControllerFilters());

        const auto& position = physics.actor->getGlobalPose().p;
        const auto  angle    = direction_angle(transform);
        physics.actor->setGlobalPose(
            px::transform(position, px::quat(angle, px::vector_3(0, 0, 1))));
    }
}
void character::init(components::character& character,
                     components::physics&   physics)
{
    px::PxCapsuleControllerDesc desc;

    auto mat = px::sdk.main->createMaterial(physics.sf, physics.df, physics.e);
    desc.radius = physics.shape_param.capsule.r;
    desc.height = physics.shape_param.capsule.hh * 2.0f;
    /** @todo Temporary values. */
    desc.stepOffset  = 0.01f;
    desc.density     = physics.density;
    desc.material    = mat;
    desc.upDirection = px::vector_3(0, 0, 1);
    desc.position    = px::vector_3ext(0, 0, 0);

    auto& controller = character.controller;
    auto& shape      = character.shape;

    controller    = world.scene.controller_manager->createController(desc);
    physics.actor = controller->getActor();
    physics.actor->userData = &physics.entity;
    controller->setUserData(&physics);

    physics.actor->getShapes(&physics.shape, 1);
    shape = physics.shape;

    physics.shape->setLocalPose(px::transform(px::z_ctrl));
}
} // namespace systems
} // namespace p201
