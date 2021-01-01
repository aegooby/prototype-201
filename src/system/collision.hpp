
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

    bool hitbox_check(entity& entity1, entity& entity2);
    bool circle_check(hitbox& hitbox1, hitbox& hitbox2);
    bool square_check(hitbox& hitbox1, hitbox& hitbox2);
    bool hybrid_check(hitbox& circle_hit, hitbox& square_hit);
    float distance(vector_3 point1, vector_3 point2);
    
};
} // namespace systems
} // namespace p201
