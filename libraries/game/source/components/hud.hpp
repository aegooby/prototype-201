
#pragma once
#include <__common.hpp>
#include <ecs.hpp>

namespace p201
{
namespace components
{
struct hud : public component
{
    using __base  = component;
    using manager = component_manager_template<components::hud>;

    static constexpr std::size_t flag = 10;

    hud(std::size_t entity) : __base(entity) { }
    virtual ~hud() override = default;
};
} // namespace components
} // namespace p201