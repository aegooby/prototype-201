
#pragma once
#include <__common.hpp>
#include <ecs.hpp>
#include <list>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <util.hpp>

namespace p201
{

class event
{
public:
    event()          = default;
    virtual ~event() = 0;
};

namespace events
{
class animation : public event
{
public:
    class entity& entity;
    std::string   name;

    animation(class entity& entity, const std::string& name);
    virtual ~animation() override = default;
};
class attack : public event
{
public:
    class entity& attacker;
    class entity& victim;

    attack(entity& attacker, entity& victim);
    virtual ~attack() override = default;
};
} // namespace events

} // namespace p201
