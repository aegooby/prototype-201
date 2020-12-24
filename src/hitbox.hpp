
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
    vector_2 center = vector_2(2);
    float    radius = 0.0f;

public:
    circle() = default;
    circle(vector_2 center, float radius) : center(center), radius(radius) { }
    circle(float x, float y, float radius) : radius(radius)
    {
        center[0] = x;
        center[1] = y;
    }
    ~circle() = default;
    // static bool check_collision(const circle& hitbox_a, const circle&
    // hitbox_b)
    // {
    //     return distance(hitbox_a.center, hitbox_b.center) <
    //            (hitbox_a.radius + hitbox_b.radius);
    // }
    inline __attribute__((always_inline)) float top() const
    {
        return center[1] + radius;
    }
    inline __attribute__((always_inline)) float bottom() const
    {
        return center[1] - radius;
    }
    inline __attribute__((always_inline)) float right() const
    {
        return center[0] + radius;
    }
    inline __attribute__((always_inline)) float left() const
    {
        return center[0] - radius;
    }
};

} // namespace p201
