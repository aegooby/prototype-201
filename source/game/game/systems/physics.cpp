
#include "physics.hpp"

#include <__common.hpp>

namespace p201
{
namespace systems
{
void physics::start() { }

void physics::update(float dt)
{
    __base::update(dt);
    for (auto& id : __registered_entities)
    {
        auto& entity    = world.entity(id);
        auto& transform = entity.component<components::transform>();
        auto& physics   = entity.component<components::physics>();

        /* Don't delete this or I will fucking slap you. */
        transform.lerp     = transform.position;
        transform.position = convert(physics.actor->getGlobalPose().p);
    }
}
void physics::init(components::physics& physics)
{
    auto mat = px::sdk.main->createMaterial(physics.sf, physics.df, physics.e);
    if (!mat) throw std::runtime_error("Failed to create material");
    auto trans  = px::PxTransform(px::PxVec3(0, 0, 0));
    auto create = [&](const auto& geometry) -> px::rigid_actor*
    {
        if (physics.dynamic)
            return px::PxCreateDynamic(*px::sdk.main, trans, geometry, *mat,
                                       physics.density);
        else
            return px::PxCreateStatic(*px::sdk.main, trans, geometry, *mat);
    };
    auto& actor = physics.actor;
    switch (physics.shape_type)
    {
        case components::physics::shape_types::capsule:
        {
            auto& __capsule = physics.shape_param.capsule;
            actor = create(px::PxCapsuleGeometry(__capsule.r, __capsule.hh));
            break;
        }
        case components::physics::shape_types::box:
        {
            auto& __box = physics.shape_param.box;
            actor = create(px::PxBoxGeometry(__box.hx, __box.hy, __box.hz));
            break;
        }
        default:
            break;
    }
    world.scene.main->addActor(*actor);
    actor->userData = &physics.entity;
    actor->getShapes(&physics.shape, 1);
}
} // namespace systems
} // namespace p201
