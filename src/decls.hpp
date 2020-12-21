
#pragma once
#include <cstddef>

namespace p201
{

using size_t = std::size_t;

namespace global
{
    static constexpr size_t game_fps = 60;
} // namespace global

template<typename value_type, size_t rows, size_t cols>
class matrix;

template<typename value_type, size_t dim>
class vector;

template<typename value_type, size_t dim>
class point;

template<typename value_type, size_t __size>
class st_array;

template<typename value_type, size_t rows, size_t columns>
class st_table;

template<typename value_type, size_t __size>
class array;

template<typename value_type, size_t rows, size_t cols>
class table;

class window;
class mouse;
class clock;
class physics_system;
class keyboard;
class engine;
class entity;
class component;
class render_component;
class transform_component;
class collision_component;
class render_system;
class sprite_base;
class sprite;
class sprite_flipbook;
class render_component;
class event_bus;
class animation_event;
class animation_complete_event;
class collision_event;
class acceleration_event;
class world;
class system;
class entity_manager;
class render_manager;
class transform_manager;
class collision_manager;

struct sprite_info;

} // namespace p201
