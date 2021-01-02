
#pragma once
#include <cstddef>

namespace p201
{

namespace global
{
static constexpr std::size_t game_fps = 60;
static constexpr bool        vsync    = true;
} // namespace global

class window;
class mouse;
class clock;
class keyboard;
class engine;
class entity;

// Components
struct component;

class world;
class system;
class entity_manager;

} // namespace p201
