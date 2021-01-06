
#include "physics.hpp"

#include "../__common.hpp"
#include "../entity_manager.hpp"
#include "../event.hpp"
#include "../util.hpp"
#include "../world.hpp"

namespace p201
{
namespace systems
{
void physics::start()
{
    world.event_manager.subscribe(*this, &physics::on_impulse_event);
    world.event_manager.subscribe(*this, &physics::on_collision_event);
}

void physics::update(float dt)
{
    __base::update(dt);
    for (auto& id : __registered_entities)
    {
        auto& entity    = world.entity(id);
        auto& transform = entity.component<components::transform>();
        auto& physics   = entity.component<components::physics>();

        /* Don't delete this or I will fucking slap you. */
        transform.lerp = transform.position;

        /* Integration */
        physics.velocity += (physics.force / physics.mass) * dt;
        transform.position += physics.velocity * dt;

        /** @todo Friction */
        physics.velocity *= 0.8f;
    }
}

void physics::impulse(components::physics& physics, const vector_3& impulse)
{
    physics.velocity += impulse / physics.mass;
}

void physics::on_impulse_event(events::impulse& event)
{
    this->impulse(event.entity.component<components::physics>(), event.vector);
}
void physics::on_collision_event(events::collision& event)
{
    /** @todo Disabled */
    auto& phys_a = event.__a.component<components::physics>();
    auto& phys_b = event.__b.component<components::physics>();

    vector_3 v_rel    = phys_b.velocity - phys_a.velocity;
    float    v_normal = v_rel.dot(event.normal);
    if (v_normal > 0) return;
    float e = std::min(phys_a.bounce, phys_b.bounce);
    float j = (-(1.0f + e) * v_normal) / (1 / phys_a.mass) + (1 / phys_b.mass);

    vector_3 impulse = j * event.normal;
    this->impulse(phys_a, -impulse);
    this->impulse(phys_b, impulse);
}
} // namespace systems
} // namespace p201
