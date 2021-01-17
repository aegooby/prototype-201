
#pragma once
#include <__common.hpp>
#include <bitset>
#include <memory>
#include <physx.hpp>
#include <string>
#include <util.hpp>

namespace p201
{
struct component
{
    static constexpr std::size_t flag      = 0;
    static constexpr std::size_t flag_bits = 32;

    std::size_t entity;

    component(std::size_t entity);
    virtual ~component() = 0;

    component(const component&) = delete;
    component(component&&)      = delete;
    component& operator=(const component&) = delete;
    component& operator=(component&&) = delete;
};

} // namespace p201
