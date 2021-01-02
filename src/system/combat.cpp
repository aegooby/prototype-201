

#include "combat.hpp"

#include "../__common.hpp"
#include "../entity.hpp"
#include "../event.hpp"
#include "../util.hpp"
#include "../window.hpp"
#include "../world.hpp"
#include "render.hpp"

namespace p201
{
namespace systems
{
void combat::start() { }
void combat::update()
{
    for (auto& id : __registered_entities)
    {
        auto& entity = world.entity(id);
        (void)entity;
    }
}
} // namespace systems
} // namespace p201
