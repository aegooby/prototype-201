
#include "collision.hpp"
#include "../quadtree.hpp"

#include "../__common.hpp"
#include "../entity_manager.hpp"
#include "../event.hpp"
#include "../world.hpp"

namespace p201
{
namespace systems
{
void collision::start() { }
void collision::update()
{
    for (auto& ref_pair : __registered_entities)
    {
        auto& entity    = ref_pair.second.get();
        auto& transform = entity.component<components::transform>();
        auto& collision = entity.component<components::collision>();
        (void)transform;
        (void)collision;
        world.quadtree.update(entity);
        
    }
}
} // namespace systems
} // namespace p201
