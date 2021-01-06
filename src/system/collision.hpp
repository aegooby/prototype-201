
#pragma once
#include "../__common.hpp"
#include "../component.hpp"
#include "../entity.hpp"
#include "../hitbox.hpp"
#include "../quadtree.hpp"
#include "system.hpp"

namespace p201
{
namespace systems
{
class collision : public system
{
public:
    using __base = system;

    quadtree quadtree;

    collision(class world& world) : __base(world), quadtree(world)
    {
        flag.set(components::transform::flag);
        flag.set(components::collision::flag);
    }
    virtual ~collision() = default;
    void         check();
    virtual void start() override;
    virtual void update(float dt) override;
};
} // namespace systems
} // namespace p201
