
#pragma once
#include "../components.hpp"

#include <__common.hpp>
#include <core.hpp>
#include <ecs.hpp>
#include <event.hpp>
#include <physx.hpp>
#include <util.hpp>

namespace p201
{
namespace systems
{
class physics : public system
{
public:
    using __base = system;

    px::PxControllerManager* physx_cm = nullptr;

    physics(class world& world) : __base(world)
    {
        flag.set(components::transform::flag);
        flag.set(components::physics::flag);
    }
    virtual ~physics() = default;
    virtual void start() override;
    virtual void update(float dt) override;
};
} // namespace systems
} // namespace p201
