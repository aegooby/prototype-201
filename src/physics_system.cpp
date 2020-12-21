
#include "physics_system.hpp"

#include "__common.hpp"
#include "entity_manager.hpp"
#include "event.hpp"
#include "world.hpp"

namespace p201
{

void physics_system::start() { }
void physics_system::update()
{
    for (auto& entity : __registered_entities)
    {
        auto& transform = entity.second.get().component<transform_component>();
        if (transform.velocity.norm() < transform.max_speed)
            transform.velocity += transform.acceleration;
        transform.position += transform.velocity;
        transform.velocity *= 0.5f;
        if (transform.velocity.norm() < 1.0f)
            transform.velocity = vector_3(0.0f, 0.0f, 0.0f);

        // auto& collision =
        // entity.second.get().component<collision_component>();

        if (entity.second.get().flag.test(system::flag::render))
        {
            auto& render  = entity.second.get().component<render_component>();
            render.rect.x = transform.position.x;
            render.rect.y = transform.position.y;
        }
    }
}

} // namespace p201
