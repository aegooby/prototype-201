
#pragma once
#include <cstddef>

namespace p201
{

namespace global
{
static constexpr float fpsfactor = 60.0f;
static constexpr bool  vsync     = true;
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
