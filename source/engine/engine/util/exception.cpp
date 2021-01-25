

#include "exception.hpp"

#include "../media-layer.hpp"

namespace p201
{
sdl_error::sdl_error(const char* what_arg) noexcept
    : __base(std::string(what_arg) + " (SDL Error: " + SDL_GetError() + ")")
{ }
sdl_error::sdl_error(const std::string& what_arg) noexcept
    : __base(what_arg + " (SDL Error: " + SDL_GetError() + ")")
{ }
sdl_error::~sdl_error() = default;
} // namespace p201