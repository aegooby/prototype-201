
#pragma once
#include "../../__common.hpp"
#include "../../physx.hpp"
#include "../../util.hpp"

#include <bitset>
#include <memory>
#include <string>

namespace p201
{
struct component
{
    static constexpr std::size_t flag      = 0;
    static constexpr std::size_t flag_bits = 32;

    std::size_t entity;

    component(std::size_t entity) : entity(entity) { }
    virtual ~component() = 0;

    component(const component&) = delete;
    component(component&&)      = delete;
    component& operator=(const component&) = delete;
    component& operator=(component&&) = delete;
};

inline component::~component() = default;

namespace components
{ } // namespace components
} // namespace p201
