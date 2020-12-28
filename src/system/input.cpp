
#include "input.hpp"

#include "../__common.hpp"
#include "../entity.hpp"
#include "../event.hpp"
#include "../event_bus.hpp"
#include "../input.hpp"
#include "../linalg.hpp"
#include "../world.hpp"
#include "system.hpp"

namespace p201
{
namespace systems
{
    void input::start() { }
    void input::update()
    {
        auto& keyboard = world.keyboard;
        auto& mouse    = world.mouse;
        (void)mouse;
        // TODO:
        static const float speed = 3.0f;
        for (auto& ref_pair : __registered_entities)
        {
            auto& entity   = ref_pair.second.get();
            auto& movement = entity.component<components::movement>();

            // Down
            if (keyboard.down(keycode::S))
            {
                movement.accel.x() -= speed / sqrt_2;
                movement.accel.y() += speed / sqrt_2;
            }
            if (keyboard.up(keycode::S))
            {
                movement.accel.x() += speed / sqrt_2;
                movement.accel.y() -= speed / sqrt_2;
            }

            // Up
            if (keyboard.down(keycode::W))
            {
                movement.accel.x() += speed / sqrt_2;
                movement.accel.y() -= speed / sqrt_2;
            }
            if (keyboard.up(keycode::W))
            {
                movement.accel.x() -= speed / sqrt_2;
                movement.accel.y() += speed / sqrt_2;
            }

            // Right
            if (keyboard.down(keycode::D))
            {
                world.event_bus.publish<animation_event>(entity, "walk-right");
                movement.accel.x() += speed / sqrt_2;
                movement.accel.y() += speed / sqrt_2;
            }
            if (keyboard.up(keycode::D))
            {
                world.event_bus.publish<animation_event>(entity, "default");
                movement.accel.x() -= speed / sqrt_2;
                movement.accel.y() -= speed / sqrt_2;
            }

            // Left
            if (keyboard.down(keycode::A))
            {
                movement.accel.x() -= speed / sqrt_2;
                movement.accel.y() -= speed / sqrt_2;
            }
            if (keyboard.up(keycode::A))
            {
                movement.accel.x() += speed / sqrt_2;
                movement.accel.y() += speed / sqrt_2;
            }

            // Jump
            if (keyboard.down(keycode::SPACE)) movement.velocity.z() += 50.0f;
        }
    }
} // namespace systems
} // namespace p201
