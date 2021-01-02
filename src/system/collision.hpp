
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
    virtual void update() override;

    static bool  hitbox_check(std::unique_ptr<hitbox>& __a,
                       std::unique_ptr<hitbox>& __b);
    static bool  circle_check(hitboxes::circle& hitbox1, hitboxes::circle& hitbox2);
    static bool  square_check(hitboxes::square& hitbox1, hitboxes::square& hitbox2);
    static bool  hybrid_check(hitboxes::circle& hitbox1, hitboxes::square& hitbox2);
    static bool  point_in_square(vector_3 circle_center, hitboxes::square& hitbox2);
    static bool  intersectCircle(hitboxes::circle& hitbox1, vector_3 point1, vector_3 point2);
    static float distance(vector_3 point1, vector_3 point2);
};
} // namespace systems
} // namespace p201
