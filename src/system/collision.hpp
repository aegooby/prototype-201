
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
    void         check();
    virtual void start() override;
    virtual void update() override;
    bool         hitbox_check(entity& entity1, entity& entity2);
};
} // namespace systems
} // namespace p201
