
#pragma once
#include "__common.hpp"
#include "ecs_common.hpp"
#include "hitbox.hpp"
#include "key.hpp"
#include "point.hpp"
#include "sprite.hpp"
#include "state.hpp"
#include "vector.hpp"

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace p201
{

class component
{
    public:
    class entity& entity;

    public:
    component(class entity& entity) : entity(entity) { }
    virtual ~component() = 0;

    // Preventing copying and moving
    component(const component&) = delete;
    component(component&&)      = delete;
    component& operator=(const component&) = delete;
    component& operator=(component&&) = delete;
};

class render_component : public component
{
    public:
    using __base = component;

    public:
    std::unordered_map<std::string, sprite_flipbook> flipbooks;
    SDL_Rect                                         rect;

    public:
    render_component(class entity& entity) : __base(entity) { }
    virtual ~render_component() = default;
    void add_flipbook(const std::string&, float, const sprite_info&);
    void remove_flipbook(const std::string&);
};

class physics_component : public component
{
    public:
    using __base = component;

    public:
    physics_component(class entity& entity) : __base(entity) { }
    virtual ~physics_component() = default;
};

class transform_component : public physics_component
{
    public:
    using __base = physics_component;

    public:
    vector_3 position;
    vector_3 velocity;
    vector_3 acceleration;
    float    max_speed = 10.0f;

    public:
    transform_component(class entity& entity) : __base(entity) { }
    virtual ~transform_component() = default;
};

class collision_component : public physics_component
{
    public:
    using __base = physics_component;

    public:
    circle hitbox;

    public:
    collision_component(class entity& entity) : __base(entity) { }
    virtual ~collision_component() = default;
};

// TODO: finish
class audio_component : public component
{
    public:
    using __base = component;

    public:
    audio_component(class entity& entity) : __base(entity) { }
    virtual ~audio_component() = default;
};

class input_component : public component
{
    public:
    using __base = component;

    public:
    public:
    input_component(class entity& entity) : __base(entity) { }
    virtual ~input_component() = default;
};

class state_component : public component
{
    public:
    using __base = component;
    //    state    state;
    public:
    state_component(class entity& entity) : __base(entity) { }
    virtual ~state_component() = default;
};

} // namespace p201
