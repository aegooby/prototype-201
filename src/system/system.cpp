
#include "system.hpp"

#include "../__common.hpp"
#include "../entity.hpp"
#include "../util.hpp"
#include "../world.hpp"

namespace p201
{

void system::register_entity(std::size_t id)
{
    if (!__registered_entities.count(id))
        __registered_entities.emplace(id);
}
void system::deregister_entity(std::size_t id)
{
    __registered_entities.erase(id);
}

void system::start() { }
void system::update(float dt)
{
    (void)dt;
}

} // namespace p201
