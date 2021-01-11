
#pragma once
#include "../__common.hpp"
#include "../linalg.hpp"

#include <list>
#include <string>
#include <typeindex>
#include <unordered_map>

namespace p201
{

class event
{
public:
    event()          = default;
    virtual ~event() = 0;
};

inline event::~event() = default;

namespace events
{
class animation : public event
{
public:
    class entity& entity;
    std::string   name;

    animation(class entity& entity, const std::string& name)
        : entity(entity), name(name)
    { }
    virtual ~animation() override = default;
};
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

} // namespace p201
