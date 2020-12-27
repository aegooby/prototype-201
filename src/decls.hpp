
#pragma once
#include <cstddef>

namespace p201
{

namespace global
{
    static constexpr std::size_t game_fps = 60;
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

class event_bus;
class world;
class system;
class entity_manager;
class render_manager;
class transform_manager;
class collision_manager;

} // namespace p201
