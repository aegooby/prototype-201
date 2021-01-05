
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
void physics::start() { }

std::tuple<vector_3, vector_3> physics::impulse(entity& entity1, entity& entity2)
{
    //elastic 2d collision
    vector_3 v1i = entity1.component<components::physics>().velocity;
    vector_3 v2i = entity2.component<components::physics>().velocity;
    float m1 = entity2.component<components::physics>().mass;
    float m2 = entity2.component<components::physics>().mass;
    
    float vcom = (m1*v1i.norm() + m2*v2i.norm())/(m1+m2);
    float v_rel = vector_3((v2i(0)-v1i(0)), (v2i(1)-v1i(1)), 0).norm();
    float theta = 0;
    
    float v1fx = ((m2/(m1+m2))*v_rel*cos(theta)) + vcom;
    float v1fy = (m2/(m1+m2))*v_rel*sin(theta);
    
    float v2fx = ((-m1/(m1+m2))*v_rel*cos(theta)) + vcom;
    float v2fy = (-m1/(m1+m2))*v_rel*sin(theta);
    
    return std::make_tuple(vector_3(v1fx, v1fy, 0), vector_3(v2fx, v2fy, 0));
}

void physics::collision_resolution(std::size_t id)
{
    auto& entity    = world.entity(id);
    auto& transform = entity.component<components::transform>();
    
    
}

void physics::update(float dt)
{
    __base::update(dt);
    for (auto& id : __registered_entities)
    {
        auto& entity    = world.entity(id);
        auto& transform = entity.component<components::transform>();
        auto& physics   = entity.component<components::physics>();
        
        if (transform.movement == true) {
            /* Don't delete this or I will fucking slap you. */
            transform.lerp = transform.position;

            physics.velocity += physics.accel * dt;
            if (physics.velocity.norm() > physics.max_speed)
            {
                physics.velocity.normalize();
                physics.velocity *= physics.max_speed;
            }
            transform.position += physics.velocity * dt;
            physics.velocity *= physics.friction;

            if (physics.velocity.norm() < 1.0f)
                physics.velocity << 0.0f, 0.0f, 0.0f;
        }
        else {
            collision_resolution(id);
        }

        
    }
}
} // namespace systems
} // namespace p201
