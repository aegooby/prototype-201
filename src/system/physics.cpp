
#include "physics.hpp"

#include "../__common.hpp"
#include "../entity_manager.hpp"
#include "../event.hpp"
#include "../physx.hpp"
#include "../util.hpp"
#include "../world.hpp"

namespace p201
{
namespace systems
{
void physics::start()
{
    // physx_cm = PxCreateControllerManager(*world.physx_scene);
}

void physics::update(float dt)
{
    __base::update(dt);
    for (auto& id : __registered_entities)
    {
        auto& entity    = world.entity(id);
        auto& transform = entity.component<components::transform>();
        auto& physics   = entity.component<components::physics>();

        /* Don't delete this or I will fucking slap you. */
        transform.lerp = transform.position;
        if (entity.flag.test(components::character::flag))
        {
            auto& character = entity.component<components::character>();
            // character.velocity += character.accel * dt;
            character.controller->move(convert(character.velocity * dt), 0.1f,
                                       dt, px::PxControllerFilters());
            transform.position =
                convert(character.controller->getFootPosition());

            px::shape* shape = nullptr;
            physics.actor->getShapes(&shape, 1);
            auto rot = px ::PxTransform(
                px::PxQuat(px::PxPiDivTwo, px::PxVec3(1, 0, 0)));
            shape->setLocalPose(rot);
        }
        else
            transform.position = convert(physics.actor->getGlobalPose().p);
    }
}
} // namespace systems
} // namespace p201
