
#pragma once
#include "__common.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "hitbox.hpp"

namespace p201
{

class collision_system : public system
{
public:
    using __base = system;

    collision_system(class world& world) : __base(world)
    {
        flag.set(system::flag::transform);
        flag.set(system::flag::collision);
    }
    virtual ~collision_system() = default;
    virtual void start() override;
    virtual void update() override;
};

} // namespace p201
