
#pragma once
#include "../components.hpp"

#include <__common.hpp>
#include <engine/core.hpp>
#include <engine/ecs.hpp>
#include <engine/event.hpp>
#include <engine/util.hpp>

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
