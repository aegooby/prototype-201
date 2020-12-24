
#include "movement_system.hpp"

#include "__common.hpp"
#include "entity_manager.hpp"
#include "event.hpp"
#include "world.hpp"

namespace p201
{

void movement_system::start() { }
void movement_system::update()
{
    for (auto& entity : __registered_entities)
    {
        auto& transform = entity.second.get().component<transform_component>();
        auto& movement  = entity.second.get().component<movement_component>();
        if (boost::numeric::ublas::norm_2(movement.velocity) <
            movement.max_speed)
            movement.velocity += movement.acceleration;
        transform.position += movement.velocity;
        movement.velocity *= friction;
        if (boost::numeric::ublas::norm_2(movement.velocity) < 1.0f)
        {
            movement.velocity[0] = 0.0f;
            movement.velocity[1] = 0.0f;
            movement.velocity[2] = 0.0f;
        }
    }
}

} // namespace p201
