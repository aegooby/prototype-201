
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

    bool  hitbox_check(std::unique_ptr<hitbox>& __a,
                       std::unique_ptr<hitbox>& __b);
    bool  circle_check(hitboxes::circle& hitbox1, hitboxes::circle& hitbox2);
    bool  square_check(hitboxes::square& hitbox1, hitboxes::square& hitbox2);
    bool  hybrid_check(hitboxes::circle&, hitboxes::square&);
    float distance(vector_3 point1, vector_3 point2);
};
} // namespace systems
} // namespace p201
