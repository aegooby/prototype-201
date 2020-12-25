
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

protected:
    matrix_3 iiso_matrix;

public:
    input_system(class world& world) : __base(world)
    {
        flag.set(component::flag::input);
        flag.set(component::flag::movement);
    }
    virtual ~input_system() = default;
    virtual void start() override;
    virtual void update() override;
};

} // namespace p201
