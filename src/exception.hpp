
#pragma once
#include "__common.hpp"

#include <exception>

namespace p201
{

class sdl_error : public std::runtime_error
{
public:
    using __base = std::runtime_error;

public:
    sdl_error(const char* what_arg) noexcept
        : __base(std::string(what_arg) + " (SDL Error: " + SDL_GetError() + ")")
    { }
    sdl_error(const std::string& what_arg) noexcept
        : __base(what_arg + " (SDL Error: " + SDL_GetError() + ")")
    { }
    virtual ~sdl_error() override = default;
};

} // namespace p201
