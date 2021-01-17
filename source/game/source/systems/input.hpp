
#pragma once
#include <__common.hpp>
#include <core.hpp>
#include <ecs.hpp>
#include <event.hpp>
#include <util.hpp>
#include "../components.hpp"

namespace p201
{
namespace systems
{
class input : public system
{
public:
    using __base = system;

    input(class world& world) : __base(world)
    {
        flag.set(components::input::flag);
        flag.set(components::character::flag);
        flag.set(components::transform::flag);
    }
    virtual ~input() override = default;
    virtual void start() override;
    virtual void update(float dt) override;
};
} // namespace systems
} // namespace p201
