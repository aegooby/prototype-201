#pragma once
#include "__common.hpp"
#include "linalg.hpp"

namespace p201
{

struct hitbox
{
    static constexpr std::size_t flag = 0;

    vector_3 center = vector_3(0.0f, 0.0f, 0.0f);

    hitbox()          = default;
    virtual ~hitbox() = default;

    virtual float top() const;
    virtual float bottom() const;
    virtual float right() const;
    virtual float left() const;
};

namespace hitboxes
{
struct circle : hitbox
{
    static constexpr std::size_t flag = 1;

    float radius = 0.0f;

    virtual ~circle() = default;
    float top() const
    {
        return center.y() + radius;
    }
    float bottom() const
    {
        return center.y() - radius;
    }
    float right() const
    {
        return center.x() + radius;
    }
    float left() const
    {
        return center.x() - radius;
    }
};

struct square : hitbox
{
    static constexpr std::size_t flag = 2;

    float width  = 0.0f;
    float height = 0.0f;

    virtual ~square() = default;

    float top() const
    {
        return center.y() + height / 2.0f;
    }

    float bottom() const
    {
        return center.y() - height / 2.0f;
    }

    float right() const
    {
        return center.x() + width / 2.0f;
    }

    float left() const
    {
        return center.x() - width / 2.0f;
    }
};
} // namespace hitboxes

} // namespace p201
