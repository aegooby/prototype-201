
#include "physics.hpp"

#include <__common.hpp>

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
        transform.lerp     = transform.position;
        transform.position = convert(physics.actor->getGlobalPose().p);
    }
}
} // namespace systems
} // namespace p201
