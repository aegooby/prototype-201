
#include "input_system.hpp"

#include "__common.hpp"
#include "entity.hpp"
#include "event.hpp"
#include "event_bus.hpp"
#include "input.hpp"
#include "world.hpp"

namespace p201
{

void input_system::start() { }
void input_system::update()
{
    // TODO: implement the rest of the input system update loop
    auto& keyboard = world.keyboard;
    // auto& mouse    = world.mouse;
    for (auto& entity : __registered_entities)
    {
        // Right
        if (keyboard.down(keycode::D))
            world.event_bus.publish<acceleration_event>(
                entity.second.get(), vector_3(10.0, 0.0, 0.0));
        if (keyboard.up(keycode::D))
            world.event_bus.publish<acceleration_event>(
                entity.second.get(), vector_3(-10.0, 0.0, 0.0));

        // Left
        if (keyboard.down(keycode::A))
            world.event_bus.publish<acceleration_event>(
                entity.second.get(), vector_3(-10.0, 0.0, 0.0));
        if (keyboard.up(keycode::A))
            world.event_bus.publish<acceleration_event>(
                entity.second.get(), vector_3(10.0, 0.0, 0.0));

        // Up
        if (keyboard.down(keycode::W))
            world.event_bus.publish<acceleration_event>(
                entity.second.get(), vector_3(0.0, -10.0, 0.0));
        if (keyboard.up(keycode::W))
            world.event_bus.publish<acceleration_event>(
                entity.second.get(), vector_3(0.0, 10.0, 0.0));

        // Down
        if (keyboard.down(keycode::S))
            world.event_bus.publish<acceleration_event>(
                entity.second.get(), vector_3(0.0, 10.0, 0.0));
        if (keyboard.up(keycode::S))
            world.event_bus.publish<acceleration_event>(
                entity.second.get(), vector_3(0.0, -10.0, 0.0));
    }
}

} // namespace p201
