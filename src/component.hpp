
#pragma once
#include "__common.hpp"
#include "hitbox.hpp"
#include "key.hpp"

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace p201
{

/**
 * @brief Components contain data only. There's no reason for a component to
 *        contain anything other than a constructor or destructor. I've broken
 *        that rule though because I'm an idiot. So this is why I have to go
 *        through this shit and add dumb ass documentation because I don't know
 *        what the fuck I'm doing.
 */
struct component
{
    enum flag
    {
        unknown   = 0,
        render    = 1,
        transform = 2,
        movement  = 3,
        collision = 4,
        input     = 5,
        audio     = 6,
    };

    static constexpr size_t flag_bits = 32;

    class entity& entity;

    component(class entity& entity) : entity(entity) { }
    virtual ~component() = 0;

    // Preventing copying and moving
    component(const component&) = delete;
    component(component&&)      = delete;
    component& operator=(const component&) = delete;
    component& operator=(component&&) = delete;
};

struct render_component : public component
{
    using __base = component;

    // TODO: placeholder (needs a texture)
    /** @brief Rectangle that sprite is rendered onto. */
    SDL_Rect rect;

    render_component(class entity& entity) : __base(entity) { }
    virtual ~render_component() = default;
};

struct transform_component : public component
{
    using __base = component;

    vector_3 position = vector_3(3);

    transform_component(class entity& entity) : __base(entity) { }
    virtual ~transform_component() = default;
};

struct movement_component : public component
{
    using __base = component;

    vector_3 velocity     = vector_3(3);
    vector_3 acceleration = vector_3(3);
    float    max_speed    = 10.0f;

    movement_component(class entity& entity) : __base(entity) { }
    virtual ~movement_component() = default;
};

struct collision_component : public component
{
    using __base = component;

    circle hitbox;

    collision_component(class entity& entity) : __base(entity) { }
    virtual ~collision_component() = default;
};

struct input_component : public component
{
    using __base = component;

    input_component(class entity& entity) : __base(entity) { }
    virtual ~input_component() = default;
};

inline component::~component() = default;

} // namespace p201
