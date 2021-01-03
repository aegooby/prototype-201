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
    virtual ~hitbox() = 0;

    virtual float top() const    = 0;
    virtual float bottom() const = 0;
    virtual float right() const  = 0;
    virtual float left() const   = 0;
};

inline hitbox::~hitbox() = default;

namespace hitboxes
{
struct circle : hitbox
{
    static constexpr std::size_t flag = 1;

    float radius = 0.0f;

    virtual ~circle() = default;
    virtual float top() const override
    {
        return center.y() - radius;
    }
    virtual float bottom() const override
    {
        return center.y() + radius;
    }
    virtual float right() const override
    {
        return center.x() + radius;
    }
    virtual float left() const override
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

    virtual float top() const override
    {
        return center.y() - height / 2.0f;
    }

    virtual float bottom() const override
    {
        return center.y() + height / 2.0f;
    }

    virtual float right() const override
    {
        return center.x() + width / 2.0f;
    }

    virtual float left() const override
    {
        return center.x() - width / 2.0f;
    }
};
} // namespace hitboxes

} // namespace p201
