
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
    world.quadtree.start(5, 1, box(0.0f, 0.0f, 500.0f, 500.0f));
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
        (void)transform;
        (void)collision;
    }
}
} // namespace systems
} // namespace p201
