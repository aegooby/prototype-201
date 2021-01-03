
#pragma once
#include "../__common.hpp"
#include "../component.hpp"
#include "../entity.hpp"
#include "system.hpp"

namespace p201
{
namespace systems
{
class movement : public system
{
public:
    using __base = system;

    movement(class world& world) : __base(world)
    {
        flag.set(components::transform::flag);
        flag.set(components::movement::flag);
    }
    virtual ~movement() = default;
    virtual void start() override;
    virtual void update(float dt) override;
};
} // namespace systems
} // namespace p201
