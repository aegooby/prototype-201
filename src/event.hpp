
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

} // namespace p201
