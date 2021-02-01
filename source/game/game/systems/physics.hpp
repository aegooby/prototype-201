
#pragma once
#include "../components.hpp"

#include <engine/__common.hpp>
#include <engine/core.hpp>
#include <engine/ecs.hpp>
#include <engine/event.hpp>
#include <engine/physx.hpp>
#include <engine/util.hpp>

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

    void init(components::physics&);
};
} // namespace systems
} // namespace p201
