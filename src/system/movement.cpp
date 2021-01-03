
#include "movement.hpp"

#include "../__common.hpp"
#include "../entity_manager.hpp"
#include "../event.hpp"
#include "../world.hpp"

namespace p201
{
namespace systems
{
void movement::start() { }
void movement::update(float dt)
{
    for (auto& id : __registered_entities)
    {
        auto& entity    = world.entity(id);
        auto& transform = entity.component<components::transform>();
        auto& movement  = entity.component<components::movement>();
        if (movement.velocity.norm() < movement.max_speed)
            movement.velocity += movement.accel * dt;
        transform.position += movement.velocity * dt;

        movement.velocity *= movement.friction;
        if (movement.velocity.norm() < 1.0f)
            movement.velocity << 0.0f, 0.0f, 0.0f;
    }
}
} // namespace systems
} // namespace p201
