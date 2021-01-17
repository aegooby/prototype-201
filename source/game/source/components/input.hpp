
#pragma once
#include <__common.hpp>
#include <ecs.hpp>

namespace p201
{
namespace components
{
struct input : public component
{
    using __base  = component;
    using manager = component_manager_template<components::input>;

    static constexpr std::size_t flag = 5;

    input(std::size_t entity) : __base(entity) { }
    virtual ~input() override = default;
};
} // namespace components
} // namespace p201