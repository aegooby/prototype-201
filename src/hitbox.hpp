
#pragma once
#include "__common.hpp"
#include "linalg.hpp"

namespace p201
{

struct hitbox
{
public:
    vector_3 center = vector_3(0.0f, 0.0f, 0.0f);
    float    radius = 0.0f;

public:
    hitbox()  = default;
    ~hitbox() = default;
    inline __attribute__((always_inline)) float top() const
    {
        return center.y() + radius;
    }
    inline __attribute__((always_inline)) float bottom() const
    {
        return center.y() - radius;
    }
    inline __attribute__((always_inline)) float right() const
    {
        return center.x() + radius;
    }
    inline __attribute__((always_inline)) float left() const
    {
        return center.x() - radius;
    }
};

} // namespace p201
