
#include "collision.hpp"

#include "../__common.hpp"
#include "../entity_manager.hpp"
#include "../event.hpp"
#include "../quadtree.hpp"
#include "../world.hpp"

namespace p201
{
namespace systems
{
void collision::start()
{
    world.quadtree.start(4, 1, box(100.0f, 100.0f, 600.0f, 600.0f));
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

bool collision::hybrid_check(hitboxes::circle& circle, hitboxes::square& square)
{
    // TODO: temp
    return false;
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
    world.quadtree.remove(__registered_entities);
    world.quadtree.insert(__registered_entities);
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
