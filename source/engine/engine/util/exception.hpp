
#pragma once
#include <__common.hpp>
#include <exception>

namespace p201
{

class sdl_error : public std::runtime_error
{
public:
    using __base = std::runtime_error;

public:
    sdl_error(const char* what_arg) noexcept;
    sdl_error(const std::string& what_arg) noexcept;
    virtual ~sdl_error() override;
};

} // namespace p201
