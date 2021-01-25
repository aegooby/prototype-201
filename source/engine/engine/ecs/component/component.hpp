
#pragma once

#include "../entity.hpp"

#include <__common.hpp>

namespace p201
{
struct component
{
    static constexpr std::size_t flag = 0;

    entity::id_t entity;

    component(entity::id_t entity);
    virtual ~component() = 0;

    component(const component&) = delete;
    component(component&&)      = delete;
    component& operator=(const component&) = delete;
    component& operator=(component&&) = delete;
};

} // namespace p201
