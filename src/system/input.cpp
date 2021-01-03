
#include "input.hpp"

#include "../__common.hpp"
#include "../entity.hpp"
#include "../event.hpp"
#include "../input.hpp"
#include "../linalg.hpp"
#include "../world.hpp"
#include "system.hpp"

namespace p201
{
namespace systems
{
void input::start() { }
void input::update(float dt)
{
    auto& keyboard = world.keyboard;
    auto& mouse    = world.mouse;
    (void)mouse;
    const float force = 1000.0f;
    for (auto& id : __registered_entities)
    {
        auto& entity    = world.entity(id);
        auto& movement  = entity.component<components::movement>();
        auto& transform = entity.component<components::transform>();

        const float accel = force / movement.mass;

        auto animation = [&entity, this](const std::string& name) {
            world.event_manager.publish<events::animation>(entity, name);
        };

        // Down
        if (keyboard.down(keycode::S))
        {
            transform.direction.set(components::transform::south);
            transform.direction.reset(components::transform::north);
            movement.accel.x() -= accel / sqrt_2;
            movement.accel.y() += accel / sqrt_2;
        }
        if (keyboard.up(keycode::S))
        {
            movement.accel.x() += accel / sqrt_2;
            movement.accel.y() -= accel / sqrt_2;
        }

        // Up
        if (keyboard.down(keycode::W))
        {
            transform.direction.set(components::transform::north);
            transform.direction.reset(components::transform::south);
            movement.accel.x() += accel / sqrt_2;
            movement.accel.y() -= accel / sqrt_2;
        }
        if (keyboard.up(keycode::W))
        {
            movement.accel.x() -= accel / sqrt_2;
            movement.accel.y() += accel / sqrt_2;
        }

        // Right
        if (keyboard.down(keycode::D))
        {
            transform.direction.set(components::transform::east);
            transform.direction.reset(components::transform::west);
            if (!keyboard.scan(keycode::A))
                animation("walk-right");
            else
                animation("stand-right");
            movement.accel.x() += accel / sqrt_2;
            movement.accel.y() += accel / sqrt_2;
        }
        if (keyboard.up(keycode::D))
        {
            transform.direction.set(components::transform::west);
            transform.direction.reset(components::transform::east);
            if (!keyboard.scan(keycode::A))
                animation("stand-right");
            else
                animation("walk-left");
            movement.accel.x() -= accel / sqrt_2;
            movement.accel.y() -= accel / sqrt_2;
        }

        // Left
        if (keyboard.down(keycode::A))
        {
            if (!keyboard.scan(keycode::D))
                animation("walk-left");
            else
                animation("stand-left");
            movement.accel.x() -= accel / sqrt_2;
            movement.accel.y() -= accel / sqrt_2;
        }
        if (keyboard.up(keycode::A))
        {
            if (!keyboard.scan(keycode::D))
                animation("stand-left");
            else
                animation("walk-right");
            movement.accel.x() += accel / sqrt_2;
            movement.accel.y() += accel / sqrt_2;
        }
    }
}
} // namespace systems
} // namespace p201
