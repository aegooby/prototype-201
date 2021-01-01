
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
