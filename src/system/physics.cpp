
#include "physics.hpp"

#include "../__common.hpp"
#include "../entity_manager.hpp"
#include "../event.hpp"
#include "../util.hpp"
#include "../world.hpp"

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
        transform.lerp = transform.position;

        physics.velocity += physics.accel * dt;
        if (physics.velocity.norm() > physics.max_speed)
        {
            physics.velocity.normalize();
            physics.velocity *= physics.max_speed;
        }
        transform.position += physics.velocity * dt;
        physics.velocity *= physics.friction;

        if (physics.velocity.norm() < 1.0f)
            physics.velocity << 0.0f, 0.0f, 0.0f;
    }
}
} // namespace systems
} // namespace p201
