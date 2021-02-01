
#include "input.hpp"

#include "../events.hpp"

#include <engine/__common.hpp>
#include <engine/core.hpp>

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

        /* Up */
        if (keyboard.down(forge::keycode::W))
            character.velocity += vector_3(400.0f, -400.0f, 0.0f);
        if (keyboard.up(forge::keycode::W))
            character.velocity += vector_3(-400.0f, 400.0f, 0.0f);

        /* Down */
        if (keyboard.down(forge::keycode::S))
            character.velocity += vector_3(-400.0f, 400.0f, 0.0f);
        if (keyboard.up(forge::keycode::S))
            character.velocity += vector_3(400.0f, -400.0f, 0.0f);

        /* Right */
        if (keyboard.down(forge::keycode::D))
            character.velocity += vector_3(400.0f, 400.0f, 0.0f);
        if (keyboard.up(forge::keycode::D))
            character.velocity += vector_3(-400.0f, -400.0f, 0.0f);

        /* Left */
        if (keyboard.down(forge::keycode::A))
            character.velocity += vector_3(-400.0f, -400.0f, 0.0f);
        if (keyboard.up(forge::keycode::A))
            character.velocity += vector_3(400.0f, 400.0f, 0.0f);

        if (keyboard.scan(forge::keycode::W))
            transform.direction = components::transform::north;
        if (keyboard.scan(forge::keycode::S))
            transform.direction = components::transform::south;
        if (keyboard.scan(forge::keycode::A))
            transform.direction = components::transform::west;
        if (keyboard.scan(forge::keycode::D))
            transform.direction = components::transform::east;
        if (keyboard.scan(forge::keycode::W, forge::keycode::A))
            transform.direction = components::transform::north_west;
        if (keyboard.scan(forge::keycode::W, forge::keycode::D))
            transform.direction = components::transform::north_east;
        if (keyboard.scan(forge::keycode::S, forge::keycode::A))
            transform.direction = components::transform::south_west;
        if (keyboard.scan(forge::keycode::S, forge::keycode::D))
            transform.direction = components::transform::south_east;

        auto speed = glm::length(character.velocity);
        switch (transform.direction)
        {
            case components::transform::north:
                break;
            case components::transform::south:
                break;
            case components::transform::east:
                if (speed > 1.0f)
                    animation_event("walk-east");
                else
                    animation_event("stand-east");
                break;
            case components::transform::west:
                if (speed > 1.0f)
                    animation_event("walk-west");
                else
                    animation_event("stand-west");
                break;
            case components::transform::north_east:
                if (speed > 1.0f)
                    animation_event("walk-north-east");
                else
                    animation_event("stand-north-east");
                break;
            case components::transform::north_west:
                break;
            case components::transform::south_east:
                break;
            case components::transform::south_west:
                break;
            default:
                throw std::runtime_error("Invalid direction");
                break;
        }
    }
}
} // namespace systems
} // namespace p201
