
#include "physics.hpp"

#include "../__common.hpp"
#include "../entity_manager.hpp"
#include "../event.hpp"
#include "../physx.hpp"
#include "../util.hpp"
#include "../world.hpp"

namespace p201
{
namespace systems
{
void physics::start() { }

void physics::update(float dt)
{
    __base::update(dt);
    for (auto& id : __registered_entities)
    {
        auto& entity    = world.entity(id);
        auto& transform = entity.component<components::transform>();

        /* Don't delete this or I will fucking slap you. */
        transform.lerp = transform.position;
    }
}
} // namespace systems
} // namespace p201
