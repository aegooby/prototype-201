
#pragma once
#include "../__common.hpp"
#include "../component.hpp"
#include "../entity.hpp"
#include "system.hpp"

namespace p201
{
namespace systems
{
    class movement : public system
    {
    public:
        using __base = system;

        movement(class world& world) : __base(world)
        {
            flag.set(component::flag::transform);
            flag.set(component::flag::movement);
        }
        virtual ~movement() = default;
        virtual void start() override;
        virtual void update() override;
    };
} // namespace systems
} // namespace p201
