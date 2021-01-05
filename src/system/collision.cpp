
#include "collision.hpp"

#include "../__common.hpp"
#include "../entity_manager.hpp"
#include "../event.hpp"
#include "../world.hpp"

#include <algorithm>

namespace p201
{
namespace systems
{
void collision::start()
{
    quadtree.start(6, 1);
    quadtree.bounds(0.0f, 0.0f, 1500.0f, 1500.0f);
}

bool collision::hitbox_check(const std::unique_ptr<hitbox>& __a,
                             const std::unique_ptr<hitbox>& __b)
{
    auto __ptr_a = __a.get();
    auto __ptr_b = __b.get();

    if (typeid(*__ptr_a) == typeid(hitboxes::circle) &&
        typeid(*__ptr_b) == typeid(hitboxes::circle))
    {
        auto& __circle_a = *dynamic_cast<hitboxes::circle*>(__ptr_a);
        auto& __circle_b = *dynamic_cast<hitboxes::circle*>(__ptr_b);
        return circle_check(__circle_a, __circle_b);
    }
    if (typeid(*__ptr_a) == typeid(hitboxes::square) &&
        typeid(*__ptr_b) == typeid(hitboxes::square))
    {
        auto& __square_a = *dynamic_cast<hitboxes::square*>(__ptr_a);
        auto& __square_b = *dynamic_cast<hitboxes::square*>(__ptr_b);
        return square_check(__square_a, __square_b);
    }
    if (typeid(*__ptr_a) == typeid(hitboxes::circle) &&
        typeid(*__ptr_b) == typeid(hitboxes::square))
    {
        auto& __circle = *dynamic_cast<hitboxes::circle*>(__ptr_a);
        auto& __square = *dynamic_cast<hitboxes::square*>(__ptr_b);
        return hybrid_check(__circle, __square);
    }
    if (typeid(*__ptr_a) == typeid(hitboxes::square) &&
        typeid(*__ptr_b) == typeid(hitboxes::circle))
    {
        auto& __square = *dynamic_cast<hitboxes::square*>(__ptr_a);
        auto& __circle = *dynamic_cast<hitboxes::circle*>(__ptr_b);
        return hybrid_check(__circle, __square);
    }
    throw std::runtime_error("Unknown hitbox types");
}

bool collision::point_in_square(const vector_3&         point,
                                const hitboxes::square& square)
{
    return (square.left() <= point.x() && square.right() >= point.x() &&
            square.top() <= point.y() && square.bottom() >= point.y());
}

bool collision::hybrid_check(const hitboxes::circle& circle,
                             const hitboxes::square& square)
{
    float circleDistance_x = abs(circle.center(0) - square.center(0));
    float circleDistance_y = abs(circle.center(1) - square.center(1));

    if (circleDistance_x > (square.width / 2 + circle.radius)) { return false; }
    if (circleDistance_y > (square.height / 2 + circle.radius))
    {
        return false;
    }

    if (circleDistance_x <= (square.width / 2)) { return true; }
    if (circleDistance_y <= (square.height / 2)) { return true; }

    float cornerDistance_sq = pow((circleDistance_x - square.width / 2), 2) +
                              pow((circleDistance_y - square.height / 2), 2);

    return (cornerDistance_sq <= (pow(circle.radius, 2)));
}

bool collision::circle_check(const hitboxes::circle& __a,
                             const hitboxes::circle& __b)
{
    return (__a.radius + __b.radius > distance(__a.center, __b.center));
}

bool collision::square_check(const hitboxes::square& __a,
                             const hitboxes::square& __b)
{

    return ((__a.left() <= __b.right()) && (__a.right() >= __b.left()) &&
            (__a.bottom() >= __b.top()) && (__a.top() <= __b.bottom()));
}

void collision::quad_check(class quadtree& quadtree)
{
    auto hitbox = [this](std::size_t id) -> auto&
    {
        return world.entity(id).component<components::collision>().hitbox;
    };
    std::list<std::vector<std::size_t>> leaves = quadtree.leaves();
    for (auto& node_entities : leaves)
    {
        for (auto& id_i : node_entities)
            for (auto& id_j : node_entities)
                if (hitbox_check(hitbox(id_i), hitbox(id_j)))
                    resolve(world.entity(id_i), world.entity(id_j));
    }
}

void collision::circle_resolve(entity& __a, entity& __b)
{
    auto& tr_a     = __a.component<components::transform>();
    auto& tr_b     = __b.component<components::transform>();
    auto& circle_a = *dynamic_cast<hitboxes::circle*>(
        __a.component<components::collision>().hitbox.get());
    auto& circle_b = *dynamic_cast<hitboxes::circle*>(
        __b.component<components::collision>().hitbox.get());

    // Vector from A to B
    vector_3 v_rel = tr_a.position - tr_b.position;
    float    rsq   = std::pow(circle_a.radius + circle_b.radius, 2);

    float    penistration    = 0.0f;
    float    v_rel_magnitude = v_rel.norm();
    vector_3 normal          = vector_3(0.0f, 0.0f, 0.0f);

    if (v_rel.norm() != 0)
    {
        penistration = rsq - v_rel_magnitude;
        /* @todo This shit is fucked thanks Randy. */
        float normal_value = rsq / v_rel_magnitude;
        normal << normal_value, normal_value, normal_value;
    }
    else
    {
        penistration = circle_a.radius;
        normal << 1.0f, 0.0f, 0.0f;
    }

    world.event_manager.publish<events::collision>(__a, __b, normal,
                                                   penistration);
}

void collision::square_resolve(entity& __a, entity& __b)
{
    auto& tr_a     = __a.component<components::transform>();
    auto& tr_b     = __b.component<components::transform>();
    auto& square_a = *dynamic_cast<hitboxes::square*>(
        __a.component<components::collision>().hitbox.get());
    auto& square_b = *dynamic_cast<hitboxes::square*>(
        __b.component<components::collision>().hitbox.get());

    vector_3 v_rel = tr_a.position - tr_b.position;

    float a_extent_x = square_a.width / 2.0f;
    float b_extent_x = square_b.width / 2.0f;

    float x_overlap = a_extent_x + b_extent_x - abs(v_rel.x());

    vector_3 normal      = vector_3(1.0f, 1.0f, 1.0f);
    float    penetration = 0.0f;

    // SAT test on x axis
    if (x_overlap > 0)
    {
        float a_extent_y = square_a.height / 2;
        float b_extent_y = square_a.height / 2;

        // Calculate overlap on y axis
        float y_overlap = a_extent_y + b_extent_y - abs(v_rel.y());

        // SAT test on y axis
        if (y_overlap > 0)
        {
            // Find out which axis is axis of least penetration
            if (x_overlap > y_overlap)
            {
                // Point towards B knowing that n points from A to B
                if (v_rel.x() < 0)
                    normal << -1.0f, 0.0f, 0.0f;
                else
                    normal << 0.0f, 0.0f, 0.0f;
                penetration = x_overlap;
            }
            else
            {
                // Point toward B knowing that n points from A to B
                if (v_rel.y() < 0)
                    normal << 0.0f, -1.0f, 0.0f;
                else
                    normal << 0.0f, 1.0f, 0.0f;
                penetration = y_overlap;
            }
        }
    }

    world.event_manager.publish<events::collision>(__a, __b, normal,
                                                   penetration);
}

void collision::hybrid_resolve(entity& __a, entity& __b)
{
    auto& tr_a   = __a.component<components::transform>();
    auto& tr_b   = __b.component<components::transform>();
    auto& square = *dynamic_cast<hitboxes::square*>(
        __a.component<components::collision>().hitbox.get());
    auto& circle = *dynamic_cast<hitboxes::circle*>(
        __b.component<components::collision>().hitbox.get());

    // Vector from A to B
    vector_3 v_rel = tr_a.position - tr_b.position;

    // Closest point on A to center of B
    vector_3 closest = v_rel;

    // Calculate half extents along each axis
    float x_extent = square.width / 2.0f;
    float y_extent = square.height / 2.0f;

    // Clamp point to edges of the AABB
    closest.x() = std::clamp(-x_extent, x_extent, closest.x());
    closest.y() = std::clamp(-y_extent, y_extent, closest.y());

    bool inside = false;
    if (v_rel == closest)
    {
        inside = true;

        // Find closest axis
        if (abs(v_rel.x()) > abs(v_rel.y()))
        {
            // Clamp to closest extent
            if (closest.x() > 0)
                closest.x() = x_extent;
            else
                closest.x() = -x_extent;
        }

        // y axis is shorter
        else
        {
            // Clamp to closest extent
            if (closest.y() > 0)
                closest.y() = y_extent;
            else
                closest.y() = -y_extent;
        }
    }

    vector_3 normal      = v_rel - closest;
    float    d           = normal.squaredNorm();
    float    r           = circle.radius;
    float    penetration = 0.0f;

    // Early out of the radius is shorter than distance to closest point and
    // Circle not inside the AABB

    // Avoided sqrt until we needed
    d = sqrt(d);

    // Collision normal needs to be flipped to point outside if circle was
    // inside the AABB
    if (inside)
    {
        normal      = -1.0f * v_rel;
        penetration = r - d;
    }
    else
    {
        normal      = v_rel;
        penetration = r - d;
    }

    world.event_manager.publish<events::collision>(__a, __b, normal,
                                                   penetration);
}

void collision::resolve(entity& __a, entity& __b)
{
    auto __ptr_a = __a.component<components::collision>().hitbox.get();
    auto __ptr_b = __b.component<components::collision>().hitbox.get();

    if (typeid(*__ptr_a) == typeid(hitboxes::circle) &&
        typeid(*__ptr_b) == typeid(hitboxes::circle))
        circle_resolve(__a, __b);
    if (typeid(*__ptr_a) == typeid(hitboxes::square) &&
        typeid(*__ptr_b) == typeid(hitboxes::square))
        square_resolve(__a, __b);
    if (typeid(*__ptr_a) == typeid(hitboxes::square) &&
        typeid(*__ptr_b) == typeid(hitboxes::circle))
        hybrid_resolve(__a, __b);
    if (typeid(*__ptr_a) == typeid(hitboxes::circle) &&
        typeid(*__ptr_b) == typeid(hitboxes::square))
        hybrid_resolve(__b, __a);
    throw std::runtime_error("Unknown hitbox types");
}

void collision::update(float dt)
{
    __base::update(dt);
    quadtree.remove(__registered_entities);
    for (auto& id : __registered_entities)
    {
        auto& entity    = world.entity(id);
        auto& transform = entity.component<components::transform>();
        auto& collision = entity.component<components::collision>();

        collision.hitbox->center.x() = transform.position.x();
        collision.hitbox->center.y() = transform.position.y();
        if (entity.flag.test(components::camera_focus::flag))
            quadtree.re_center(transform.position);
    }
    quadtree.insert(__registered_entities);
    quad_check(quadtree);
}
} // namespace systems
} // namespace p201
