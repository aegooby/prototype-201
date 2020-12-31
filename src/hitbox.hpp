
#pragma once
#include "__common.hpp"
#include "linalg.hpp"

namespace p201
{

struct hitbox
{
};

struct circle : public hitbox
{
public:
    vector_2 center;
    float    radius = 0.0f;

public:
    circle() = default;
    circle(vector_2 center, float radius) : center(center), radius(radius) { }
    circle(float x, float y, float radius) : radius(radius)
    {
        center.x() = x;
        center.y() = y;
    }
    ~circle() = default;
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
