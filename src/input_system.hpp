
#pragma once
#include "__common.hpp"
#include "system.hpp"
#include "world.hpp"

namespace p201
{

class input_system : public system
{
public:
    using __base = system;

public:
    input_system(class world& world) : __base(world)
    {
        flag.set(system::flag::input);
        flag.set(system::flag::movement);
    }
    virtual ~input_system() = default;
    virtual void start() override;
    virtual void update() override;
};

} // namespace p201
