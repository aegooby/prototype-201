
#pragma once
#include "__common.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "hitbox.hpp"

namespace p201
{

class physics_system : public system
{
public:
    using __base = system;

protected:
public:
    physics_system(class world& world) : __base(world)
    {
        flag.set(system::flag::collision);
        flag.set(system::flag::transform);
    }
    virtual ~physics_system() = default;
    virtual void start() override;
    virtual void update() override;
};

} // namespace p201
