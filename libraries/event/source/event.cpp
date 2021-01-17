
#include "event.hpp"

namespace p201
{
event::~event() = default;

namespace events
{
animation::animation(class entity& entity, const std::string& name)
    : entity(entity), name(name)
{ }
attack::attack(entity& attacker, entity& victim)
    : attacker(attacker), victim(victim)
{ }
} // namespace events

} // namespace p201
