
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

    /** @brief Whether or not to display the sprite on rendering. */
    bool visible = true;
    /** @brief Whether to transform the rendering to isometric. */
    bool iso = true;
    /** @brief Family of flipbooks associated with this component. */
    std::string family = "unknown";
    /** @brief Floating point rect that textures are rendered onto. */
    SDL_FRect rect = { .x = 0.0f, .y = 0.0f, .w = 0.0f, .h = 0.0f };
    /** @brief Portion of source rectangle to be rendered. */
    SDL_Rect srcrect = { .x = 0, .y = 0, .w = 0, .h = 0 };
    /** @brief Texture rendered onto rect. */
    SDL_Texture* texture = nullptr;
    /** @brief The displacement factor of the sprite from its center point. */
    vector_2 offset = vector_2(0.0f, 0.0f);

    render(class entity& entity) : __base(entity) { }
    virtual ~render() = default;
};

struct transform : public component
{
    using __base = component;

    static constexpr std::size_t flag = 2;

    /** @brief Used in direction bitset. */
    enum
    {
        north = 0,
        south = 1,
        east  = 2,
        west  = 3,
    };

    /** @brief Previous coordinate used to interpolate in updates. */
    vector_3 lerp = vector_3(0.0f, 0.0f, 0.0f);
    /** @brief Game coordinate position (not isometric position). */
    vector_3 position = vector_3(0.0f, 0.0f, 0.0f);
    /** @brief Direction the entity is facing (not always used). */
    std::bitset<4> direction;

    transform(class entity& entity) : __base(entity) { }
    virtual ~transform() = default;
};

struct movement : public component
{
    using __base = component;

    static constexpr std::size_t flag = 3;

    vector_3 velocity  = vector_3(0.0f, 0.0f, 0.0f);
    vector_3 accel     = vector_3(0.0f, 0.0f, 0.0f);
    float    max_speed = 0.0f;
    float    friction  = 0.0f;
    float    mass      = 0.0f;

    movement(class entity& entity) : __base(entity) { }
    virtual ~movement() = default;
};

struct collision : public component
{
    using __base = component;

    static constexpr std::size_t flag = 4;

    std::unique_ptr<hitbox> hitbox = nullptr;

    collision(class entity& entity) : __base(entity) { }
    virtual ~collision() = default;
};

struct input : public component
{
    using __base = component;

    static constexpr std::size_t flag = 5;

    float force = 0.0f;

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

    bool     focus = false;
    vector_2 shift = vector_2(0.0f, 0.0f);

    camera(class entity& entity) : __base(entity) { }
    virtual ~camera() = default;
};

struct health : public component
{
    using __base = component;

    static constexpr std::size_t flag = 8;

    float hp         = 0.0f;
    float max_hp     = 0.0f;
    float shield     = 0.0f;
    float max_shield = 0.0f;

    health(class entity& entity) : __base(entity) { }
    virtual ~health() = default;
};

struct hud : public component
{
    using __base = component;

    static constexpr std::size_t flag = 9;

    hud(class entity& entity) : __base(entity) { }
    virtual ~hud() = default;
};
} // namespace components
} // namespace p201
