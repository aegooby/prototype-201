
#pragma once
#include "../__common.hpp"
#include "../component.hpp"
#include "../entity.hpp"
#include "../event.hpp"
#include "system.hpp"

namespace p201
{
namespace systems
{
class physics : public system
{
public:
    using __base = system;

    physics(class world& world) : __base(world)
    {
        flag.set(components::transform::flag);
        flag.set(components::physics::flag);
    }
    virtual ~physics() = default;
    virtual void start() override;
    virtual void update(float dt) override;

    void impulse(components::physics& physics, const vector_3& impulse);

    void on_impulse_event(events::impulse&);
    void on_collision_event(events::collision&);
};
} // namespace systems
} // namespace p201
