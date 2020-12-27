
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
    void movement::update()
    {
        for (auto& entity : __registered_entities)
        {
            auto& transform =
                entity.second.get().component<transform_component>();
            auto& movement =
                entity.second.get().component<movement_component>();
            if (movement.velocity.norm() < movement.max_speed)
                movement.velocity += movement.accel;
            transform.position += movement.velocity;
            movement.velocity *= movement.friction;
            if (movement.velocity.norm() < 1.0f)
                movement.velocity << 0.0f, 0.0f, 0.0f;
        }
    }
} // namespace systems
} // namespace p201
