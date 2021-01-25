
#pragma once
#include <engine/ecs.hpp>
#include <engine/event.hpp>

namespace p201
{
namespace events
{
class attack : public event
{
public:
    class entity& attacker;
    class entity& victim;

    attack(entity& attacker, entity& victim)
        : attacker(attacker), victim(victim)
    { }
    virtual ~attack() override = default;
};
} // namespace events
}