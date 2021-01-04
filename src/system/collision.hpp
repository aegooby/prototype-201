
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

    static bool hitbox_check(const std::unique_ptr<hitbox>&,
                             const std::unique_ptr<hitbox>&);
    static bool circle_check(const hitboxes::circle&, const hitboxes::circle&);
    static bool square_check(const hitboxes::square&, const hitboxes::square&);
    static bool hybrid_check(const hitboxes::circle&, const hitboxes::square&);
    static bool point_in_square(const vector_3&, const hitboxes::square&);
    
    void quad_check(node& node);
    void quad_check(class quadtree& quadtree);
};
} // namespace systems
} // namespace p201
