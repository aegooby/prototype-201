
#pragma once
#include "__common.hpp"
#include "state.hpp"
#include "vector.hpp"

#include <list>
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

class animation_event : public event
{
    public:
    class entity& entity;

    public:
    animation_event(class entity& entity) : entity(entity) { }
    virtual ~animation_event() = default;
};

class animation_complete_event : public event
{
    public:
    class entity& entity;

    public:
    animation_complete_event(class entity& entity) : entity(entity) { }
    virtual ~animation_complete_event() = default;
};

class collision_event : public event
{
    public:
    class entity& entity_a;
    class entity& entity_b;

    public:
    collision_event(class entity& entity_a, class entity& entity_b)
        : entity_a(entity_a), entity_b(entity_b)
    {
    }
    virtual ~collision_event() = default;
};

class acceleration_event : public event
{
    public:
    enum class mode
    {
        mod,
        set,
    };
    class entity& entity;
    vector_3      acceleration;
    mode          mode;

    public:
    acceleration_event(class entity& entity, vector_3 acceleration,
                       enum mode mode)
        : entity(entity), acceleration(acceleration), mode(mode)
    {
    }
    virtual ~acceleration_event() = default;
};

} // namespace p201
