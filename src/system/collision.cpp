
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
}
} // namespace systems
} // namespace p201
