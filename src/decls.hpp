
#pragma once
#include <cstddef>

namespace p201
{

using size_t = std::size_t;

namespace global
{
    static constexpr size_t game_fps = 60;
} // namespace global

class window;
class mouse;
class clock;
class keyboard;
class engine;
class entity;

// Components
struct component;
struct render_component;
struct transform_component;
struct movement_component;
struct collision_component;

class render_system;
class sprite_base;
class sprite;
class sprite_flipbook;
class event_bus;
class animation_event;
class animation_complete_event;
class collision_event;
class world;
class system;
class entity_manager;
class render_manager;
class transform_manager;
class collision_manager;

struct sprite_info;

} // namespace p201
