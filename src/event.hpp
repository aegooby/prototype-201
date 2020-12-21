
#pragma once
#include "__common.hpp"
#include "vector.hpp"

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

class acceleration_event : public event
{
public:
    class entity& entity;
    vector_3      vector;

    acceleration_event(class entity& entity, vector_3 vector)
        : entity(entity), vector(vector)
    {
    }
    virtual ~acceleration_event() = default;
};

} // namespace p201
