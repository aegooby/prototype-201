
#include "movement_system.hpp"

#include "__common.hpp"
#include "entity_manager.hpp"
#include "event.hpp"
#include "world.hpp"

namespace p201
{

void movement_system::start()
{
    world.event_bus.subscribe(*this, &movement_system::on_acceleration_event);
}
void movement_system::update()
{
    for (auto& entity : __registered_entities)
    {
        auto& transform = entity.second.get().component<transform_component>();
        auto& movement  = entity.second.get().component<movement_component>();
        if (movement.velocity.norm() < movement.max_speed)
            movement.velocity += movement.acceleration;
        transform.position += movement.velocity;
        movement.velocity *= friction;
        if (movement.velocity.norm() < 1.0f)
            movement.velocity = vector_3(0.0f, 0.0f, 0.0f);
    }
}

void movement_system::on_acceleration_event(acceleration_event& event)
{
    auto& movement = event.entity.component<movement_component>();
    movement.acceleration += event.vector;
}

} // namespace p201
