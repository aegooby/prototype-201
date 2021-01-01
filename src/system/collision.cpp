
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

bool collision::hitbox_check(entity& entity1, entity& entity2)
{
    hitbox1 = entity1.hitbox;
    hitbox2 = entity2.hitbox;
    
    if (typeid(hitbox1) == typeid(circle) && typeid(hitbox2) == typeid(circle)) {
        return circle_check(hitbox1, hitbox2);
    }
    else if (typeid(hitbox1) == typeid(square) && typeid(hitbox2) == typeid(square)) {
        return square_check(hitbox1, hitbox2);
    }
    else {
        if (typeid(hitbox1) == typeid(circle)) {
            return hybrid_check(hitbox1, hitbox2);
        }
        else {
            return hybrid_check(hitbox2, hitbox1);
        }
    }
}

float collision::distance(vector_3 point1, vector_3 point2) {
    return sqrt(pow((point1(0)+point2(0)),2)+pow((point1(1)+point2(1)),2));
}

bool collision::hybrid_check(hitbox& circle_hit, hitbox& circle_square) {
    
}

bool collision::circle_check(hitbox& hitbox1, hitbox& hitbox2) {
    if (hitbox1.radius+hitbox2.radius > distance(hitbox1.center, hitbox2.center)) {
        return true;
    }
    else {
        return false;
    }
}

bool collision::square_check(hitbox& hitbox1, hitbox& hitbox2) {
    float left1 = hitbox1.center - hitbox1.width;
    float right1 = hitbox1.center + hitbox1.width;
    float top1 = hitbox1.center + hitbox1.height;
    float bot1 = hitbox1.center - hitbox1.height;
    
    float left2 = hitbox2.center - hitbox2.width;
    float right2 = hitbox2.center + hitbox2.width;
    float top2 = hitbox2.center + hitbox2.height;
    float bot2 = hitbox2.center - hitbox2.height;
    
    if ((left1 < right2) &&
        (right1 > left2) &&
        (bot1 < top2) &&
        (top1 > bot2)) {
        return true;
    }
    else {
        return false;
    }
    
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

        collision.hitbox.center.x() = transform.position.x();
        collision.hitbox.center.y() = transform.position.y();
    }
}
} // namespace systems
} // namespace p201
