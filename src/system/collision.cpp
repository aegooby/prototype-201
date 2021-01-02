
#include "collision.hpp"

#include "../__common.hpp"
#include "../entity_manager.hpp"
#include "../event.hpp"
#include "../world.hpp"

namespace p201
{
namespace systems
{
void collision::start()
{
    quadtree.start(4, 1, box(100.0f, 100.0f, 600.0f, 600.0f));
}

bool collision::hitbox_check(std::unique_ptr<hitbox>& __a,
                             std::unique_ptr<hitbox>& __b)
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

float collision::distance(vector_3 point1, vector_3 point2)
{
    return sqrt(pow((point1(0) + point2(0)), 2) +
                pow((point1(1) + point2(1)), 2));
}

bool  collision::point_in_square(vector_3 circle_center, hitboxes::square& hitbox2)
{
    return (hitbox2.left() <= circle_center(0) &&
            hitbox2.right() >= circle_center(0) &&
            hitbox2.top() <= circle_center(1) &&
            hitbox2.bottom() >= circle_center(1));
}

bool  collision::intersectCircle(hitboxes::circle& hitbox1, vector_3 point1, vector_3 point2)
{
    float dist = (abs((point2(0)-point1(0))*(point1(1)-hitbox1.center(1)) - (point1(0)-hitbox1.center(0))*(point2(1)-point1(1)))/(distance(point1, point2)));
    
    return dist < hitbox1.radius;
}

bool collision::hybrid_check(hitboxes::circle& circle, hitboxes::square& square)
{
    if (point_in_square(circle.center, square)) { return true; }
    else {
        vector_3 bot_left = vector_3(square.left(), square.bottom(), 0);
        vector_3 bot_right = vector_3(square.right(), square.bottom(), 0);
        vector_3 top_left = vector_3(square.left(), square.top(), 0);
        vector_3 top_right = vector_3(square.right(), square.top(), 0);
        
        return (intersectCircle(circle, bot_left, bot_right) ||
                intersectCircle(circle, bot_right, top_right) ||
                intersectCircle(circle, top_right, top_left) ||
                intersectCircle(circle, top_left, bot_left));
    }
}

bool collision::circle_check(hitboxes::circle& __a, hitboxes::circle& __b)
{
    return (__a.radius + __b.radius > distance(__a.center, __b.center));
}

bool collision::square_check(hitboxes::square& __a, hitboxes::square& __b)
{

    return ((__a.left() < __b.right()) && (__a.right() > __b.left()) &&
            (__a.bottom() < __b.top()) && (__a.top() > __b.bottom()));
}

void collision::update()
{
    quadtree.remove(__registered_entities);
    quadtree.insert(__registered_entities);
    for (auto& id : __registered_entities)
    {
        auto& entity    = world.entity(id);
        auto& transform = entity.component<components::transform>();
        auto& collision = entity.component<components::collision>();

        collision.hitbox->center.x() = transform.position.x();
        collision.hitbox->center.y() = transform.position.y();
    }
}
} // namespace systems
} // namespace p201
