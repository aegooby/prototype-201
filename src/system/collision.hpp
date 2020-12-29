
#pragma once
#include "../__common.hpp"
#include "../component.hpp"
#include "../entity.hpp"
#include "../hitbox.hpp"
#include "system.hpp"

namespace p201
{
namespace systems
{
class collision : public system
{
public:
    using __base = system;

    collision(class world& world) : __base(world)
    {
        flag.set(components::transform::flag);
        flag.set(components::collision::flag);
    }
    virtual ~collision() = default;
    virtual void start() override;
    virtual void update() override;
};
} // namespace systems
} // namespace p201
