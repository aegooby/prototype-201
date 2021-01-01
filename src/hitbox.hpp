#pragma once
#include "__common.hpp"
#include "linalg.hpp"

namespace p201
{

struct hitbox
{
public:
    vector_3 center = vector_3(0.0f, 0.0f, 0.0f);
    
public:
    hitbox()  = default;
    ~hitbox() = default;
    virtual float top() const;
    virtual float bottom() const;
    virtual float right() const;
    virtual float left() const;
};


struct circle : hitbox
{
public:
    float    radius = 0.0f;
    
public:
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
public:
    float    width = 0.0f;
    float    height = 0.0f;
    
public:
    float top() const
    {
        return center.y() + height;
    }
    
    float bottom() const
    {
        return center.y() - height;
    }
    
    float right() const
    {
        return center.x() + width;
    }
    
    float left() const
    {
        return center.x() - width;
    }
};

} // namespace p201
