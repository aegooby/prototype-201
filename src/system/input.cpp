
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

        auto animation_event = [&entity, this](const std::string& name)
        { world.event_manager.publish<events::animation>(entity, name); };

        /* Down */
        if (keyboard.down(keycode::S))
        {
            transform.direction.set(components::transform::south);
            transform.direction.reset(components::transform::north);
            if (!keyboard.scan(keycode::A))
                transform.direction.reset(components::transform::west);
            if (!keyboard.scan(keycode::D))
                transform.direction.reset(components::transform::east);

            /* -, + */
            character.velocity += vector_3(-400.0f, 400.0f, 0.0f);
        }
        if (keyboard.up(keycode::S))
        {
            if (keyboard.scan(keycode::A))
                transform.direction.reset(components::transform::south);
            if (keyboard.scan(keycode::D))
                transform.direction.reset(components::transform::south);
            if (keyboard.scan(keycode::W))
                transform.direction.reset(components::transform::south);

            /* +, - */
            character.velocity += vector_3(400.0f, -400.0f, 0.0f);
        }

        /* Up */
        if (keyboard.down(keycode::W))
        {
            transform.direction.set(components::transform::north);
            transform.direction.reset(components::transform::south);
            if (!keyboard.scan(keycode::A))
                transform.direction.reset(components::transform::west);
            if (!keyboard.scan(keycode::D))
                transform.direction.reset(components::transform::east);

            /* +, - */
            character.velocity += vector_3(400.0f, -400.0f, 0.0f);
        }
        if (keyboard.up(keycode::W))
        {
            if (keyboard.scan(keycode::A))
                transform.direction.reset(components::transform::north);
            if (keyboard.scan(keycode::D))
                transform.direction.reset(components::transform::north);
            if (keyboard.scan(keycode::S))
                transform.direction.reset(components::transform::north);

            /* -, + */
            character.velocity += vector_3(-400.0f, 400.0f, 0.0f);
        }

        /* Right */
        if (keyboard.down(keycode::D))
        {
            transform.direction.set(components::transform::east);
            transform.direction.reset(components::transform::west);
            if (!keyboard.scan(keycode::W))
                transform.direction.reset(components::transform::north);
            if (!keyboard.scan(keycode::S))
                transform.direction.reset(components::transform::south);

            if (!keyboard.scan(keycode::A))
                animation_event("walk-right");
            else
                animation_event("stand-right");

            /* +, + */
            character.velocity += vector_3(400.0f, 400.0f, 0.0f);
        }
        if (keyboard.up(keycode::D))
        {
            if (keyboard.scan(keycode::W))
                transform.direction.reset(components::transform::east);
            if (keyboard.scan(keycode::S))
                transform.direction.reset(components::transform::east);
            if (keyboard.scan(keycode::A))
                transform.direction.reset(components::transform::east);

            if (!keyboard.scan(keycode::A))
                animation_event("stand-right");
            else
                animation_event("walk-left");

            /* -, - */
            character.velocity += vector_3(-400.0f, -400.0f, 0.0f);
        }

        /* Left */
        if (keyboard.down(keycode::A))
        {
            transform.direction.set(components::transform::west);
            transform.direction.reset(components::transform::east);
            if (!keyboard.scan(keycode::W))
                transform.direction.reset(components::transform::north);
            if (!keyboard.scan(keycode::S))
                transform.direction.reset(components::transform::south);

            if (!keyboard.scan(keycode::D))
                animation_event("walk-left");
            else
                animation_event("stand-left");

            /* -, - */
            character.velocity += vector_3(-400.0f, -400.0f, 0.0f);
        }
        if (keyboard.up(keycode::A))
        {
            if (keyboard.scan(keycode::W))
                transform.direction.reset(components::transform::west);
            if (keyboard.scan(keycode::S))
                transform.direction.reset(components::transform::west);
            if (keyboard.scan(keycode::D))
                transform.direction.reset(components::transform::west);

            if (!keyboard.scan(keycode::D))
                animation_event("stand-left");
            else
                animation_event("walk-right");

            /* +, + */
            character.velocity += vector_3(400.0f, 400.0f, 0.0f);
        }

        std::cout << transform.direction << std::endl;
    }
}
} // namespace systems
} // namespace p201
