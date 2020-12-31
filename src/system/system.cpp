
#include "system.hpp"

#include "../__common.hpp"
#include "../entity.hpp"
#include "../world.hpp"

namespace p201
{

void system::register_entity(class entity& entity)
{
    if (!__registered_entities.contains(entity.id))
        __registered_entities.emplace(entity.id);
}
void system::deregister_entity(class entity& entity)
{
    __registered_entities.erase(entity.id);
}

} // namespace p201
