
#pragma once
#include "../__common.hpp"
#include "../world.hpp"
#include "system.hpp"

namespace p201
{
namespace systems
{
class input : public system
{
private:
    physx::PxControllerManager* manager = nullptr;

public:
    using __base = system;

    input(class world& world)
        : __base(world), manager(PxCreateControllerManager(*world.scene.main))
    {
        flag.set(components::input::flag);
        flag.set(components::physics::flag);
        flag.set(components::transform::flag);
    }
    virtual ~input()
    {
        manager->release();
    }
    virtual void start() override;
    virtual void update(float dt) override;
};
} // namespace systems
} // namespace p201
