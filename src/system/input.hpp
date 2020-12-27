
#pragma once
#include "../__common.hpp"
#include "../world.hpp"
#include "system.hpp"

namespace p201
{
namespace systems
{
    class input : public system
    {
    public:
        using __base = system;

        input(class world& world) : __base(world)
        {
            flag.set(component::flag::input);
            flag.set(component::flag::movement);
        }
        virtual ~input() = default;
        virtual void start() override;
        virtual void update() override;
    };
} // namespace systems
} // namespace p201
