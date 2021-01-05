
#pragma once
#include "../__common.hpp"
#include "../linalg.hpp"

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
    {
    }
    virtual ~animation() = default;
};
class collision : public event
{
public:
    class entity& __a;
    class entity& __b;
    vector_3      normal;
    float         depth;

    collision(entity& __a, class entity& __b, const vector_3& normal,
              float depth)
        : __a(__a), __b(__b), normal(normal), depth(depth)
    {
    }
    virtual ~collision() = default;
};
} // namespace events

} // namespace p201
