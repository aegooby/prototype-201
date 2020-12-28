
#pragma once
#include "__common.hpp"
#include "linalg.hpp"

#include <list>
#include <typeindex>
#include <unordered_map>

// TODO: add event blockers

namespace p201
{

class event
{
public:
    event()          = default;
    virtual ~event() = 0;
};

inline event::~event() = default;

class animation_event : public event
{
public:
    class entity& entity;
    std::string   name;

    animation_event(class entity& entity, const std::string& name)
        : entity(entity), name(name)
    {
    }
    virtual ~animation_event() = default;
};

} // namespace p201
