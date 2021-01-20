
#pragma once
#include <cstddef>

namespace p201
{
class window;
class mouse;
class clock;
class keyboard;
class engine;
class entity;

struct component;

class world;
class system;
class entity_manager;

namespace handle_types
{
using renderer = SDL_Renderer;
using window   = SDL_Window;
} // namespace handle_types

} // namespace p201
