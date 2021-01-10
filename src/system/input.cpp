
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
    __base::update(dt);
    auto& keyboard = world.keyboard;
    for (auto& id : __registered_entities)
    {
        auto& entity    = world.entity(id);
        auto& transform = entity.component<components::transform>();
        auto& character = entity.component<components::character>();

        auto animation = [&entity, this](const std::string& name)
        { world.event_manager.publish<events::animation>(entity, name); };

        /* Down */
        if (keyboard.down(keycode::S))
        {
            transform.direction.set(components::transform::south);
            transform.direction.reset(components::transform::north);
            character.accel += vector_3(-5000.0f, 5000.0f, 0.0f);
            /* -, + */
        }
        if (keyboard.up(keycode::S))
        {
            character.accel += vector_3(5000.0f, -5000.0f, 0.0f);
            /* +, - */
        }

        /* Up */
        if (keyboard.down(keycode::W))
        {
            transform.direction.set(components::transform::north);
            transform.direction.reset(components::transform::south);
            character.accel += vector_3(5000.0f, -5000.0f, 0.0f);
            /* +, - */
        }
        if (keyboard.up(keycode::W))
        {
            character.accel += vector_3(-5000.0f, 5000.0f, 0.0f);
            /* -, + */
        }

        /* Right */
        if (keyboard.down(keycode::D))
        {
            transform.direction.set(components::transform::east);
            transform.direction.reset(components::transform::west);
            if (!keyboard.scan(keycode::A))
                animation("walk-right");
            else
                animation("stand-right");
            character.accel += vector_3(5000.0f, 5000.0f, 0.0f);
            /* +, + */
        }
        if (keyboard.up(keycode::D))
        {
            transform.direction.set(components::transform::west);
            transform.direction.reset(components::transform::east);
            if (!keyboard.scan(keycode::A))
                animation("stand-right");
            else
                animation("walk-left");
            character.accel += vector_3(-5000.0f, -5000.0f, 0.0f);
            /* -, - */
        }

        /* Left */
        if (keyboard.down(keycode::A))
        {
            if (!keyboard.scan(keycode::D))
                animation("walk-left");
            else
                animation("stand-left");
            character.accel += vector_3(-5000.0f, -5000.0f, 0.0f);
            /* -, - */
        }
        if (keyboard.up(keycode::A))
        {
            if (!keyboard.scan(keycode::D))
                animation("stand-left");
            else
                animation("walk-right");
            character.accel += vector_3(5000.0f, 5000.0f, 0.0f);
            /* +, + */
        }
    }
}
} // namespace systems
} // namespace p201
