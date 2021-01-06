
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
    world.event_manager.subscribe(*this, &physics::on_collision_event);
}

std::tuple<vector_3, vector_3> physics::impulse(entity& __a, entity& __b)
{
    // elastic 2d collision
    return std::tuple<vector_3, vector_3>();
    // vector_3 v1i = entity1.component<components::physics>().velocity;
    // vector_3 v2i = entity2.component<components::physics>().velocity;
    // float    m1  = entity2.component<components::physics>().mass;
    // float    m2  = entity2.component<components::physics>().mass;
    //
    // float vcom  = (m1 * v1i.norm() + m2 * v2i.norm()) / (m1 + m2);
    // float v_rel = vector_3((v2i(0) - v1i(0)), (v2i(1) - v1i(1)), 0).norm();
    // float theta = 0;
    //
    // float v1fx = ((m2 / (m1 + m2)) * v_rel * cos(theta)) + vcom;
    // float v1fy = (m2 / (m1 + m2)) * v_rel * sin(theta);
    //
    // float v2fx = ((-m1 / (m1 + m2)) * v_rel * cos(theta)) + vcom;
    // float v2fy = (-m1 / (m1 + m2)) * v_rel * sin(theta);
    //
    // return std::make_tuple(vector_3(v1fx, v1fy, 0), vector_3(v2fx, v2fy, 0));
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
        /** @todo Add position/velocity updates */
    }
}
void physics::on_collision_event(events::collision& event)
{
    auto& phys_a = event.__a.component<components::physics>();
    auto& phys_b = event.__b.component<components::physics>();
    // Calculate relative velocity
    vector_3 v_rel = phys_b.velocity - phys_a.velocity;

    // Calculate relative velocity in terms of the normal direction
    float v_normal = v_rel.dot(event.normal);

    // Do not resolve if velocities are separating
    if (v_normal > 0) return;

    // Calculate restitution
    float e = std::min(phys_a.bounce, phys_b.bounce);

    // Calculate impulse scalar
    float j = (-(1.0f + e) * v_normal) / (1 / phys_a.mass) + (1 / phys_b.mass);

    // Apply impulse
    vector_3 impulse = j * event.normal;
    phys_a.velocity -= 1 / phys_a.mass * impulse;
    phys_b.velocity += 1 / phys_b.mass * impulse;
}
} // namespace systems
} // namespace p201
