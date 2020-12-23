
#pragma once
#include "__common.hpp"
#include "component.hpp"
#include "entity.hpp"

namespace p201
{

static const float friction = 0.6f;

class movement_system : public system
{
public:
    using __base = system;

    movement_system(class world& world) : __base(world)
    {
        flag.set(system::flag::transform);
        flag.set(system::flag::movement);
    }
    virtual ~movement_system() = default;
    virtual void start() override;
    virtual void update() override;
};

} // namespace p201
