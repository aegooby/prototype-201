
#pragma once
#include "../__common.hpp"
#include "../hitbox.hpp"
#include "../key.hpp"
#include "../sprite.hpp"

#include <string>
#include <typeindex>
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
    static constexpr std::size_t flag      = 0;
    static constexpr std::size_t flag_bits = 32;

    class entity& entity;

    component(class entity& entity) : entity(entity) { }
    virtual ~component() = 0;

    // Preventing copying and moving
    component(const component&) = delete;
    component(component&&)      = delete;
    component& operator=(const component&) = delete;
    component& operator=(component&&) = delete;
};

inline component::~component() = default;

namespace components
{
struct render : public component
{
    using __base = component;

    static constexpr std::size_t flag = 1;

    bool visible = true;
    /** @brief Family of flipbooks associated with this component. */
    std::string family = "unknown";
    /** @brief Floating point rect that textures are rendered onto. */
    SDL_FRect rect = { .x = 0.0f, .y = 0.0f, .w = 0.0f, .h = 0.0f };
    /** @brief Texture rendered onto rect. */
    SDL_Texture* texture = nullptr;
    /** @brief The displacement factor of the sprite from its center point. */
    vector_2 displacement;

    render(class entity& entity) : __base(entity) { }
    virtual ~render() = default;
};

struct transform : public component
{
    using __base = component;

    static constexpr std::size_t flag = 2;

    /** @brief Game coordinate position (not isometric position). */
    vector_3 position = vector_3(0.0f, 0.0f, 0.0f);

    transform(class entity& entity) : __base(entity) { }
    virtual ~transform() = default;
};

struct movement : public component
{
    using __base = component;

    static constexpr std::size_t flag = 3;

    vector_3 velocity  = vector_3(0.0f, 0.0f, 0.0f);
    vector_3 accel     = vector_3(0.0f, 0.0f, 0.0f);
    float    max_speed = 10.0f;
    float    friction  = 0.6f;

    movement(class entity& entity) : __base(entity) { }
    virtual ~movement() = default;
};

struct collision : public component
{
    using __base = component;

    static constexpr std::size_t flag = 4;

    hitbox hitbox;

    collision(class entity& entity) : __base(entity) { }
    virtual ~collision() = default;
};

struct input : public component
{
    using __base = component;

    static constexpr std::size_t flag = 5;

    input(class entity& entity) : __base(entity) { }
    virtual ~input() = default;
};

struct animation : public component
{
    using __base = component;

    static constexpr std::size_t flag = 6;

    std::string name      = "default";
    std::size_t frame     = 0;
    std::size_t index     = 0;
    float       fps       = 0.0f;
    bool        interrupt = false;
    bool        loop      = true;

    animation(class entity& entity) : __base(entity) { }
    virtual ~animation() = default;
};

struct camera : public component
{
    using __base = component;

    static constexpr std::size_t flag = 7;

    std::size_t priority = 0;

    camera(class entity& entity) : __base(entity) { }
    virtual ~camera() = default;
};
} // namespace components
} // namespace p201
