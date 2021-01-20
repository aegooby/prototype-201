
#pragma once
#include "../components.hpp"

#include <__common.hpp>
#include <core.hpp>
#include <ecs.hpp>
#include <event.hpp>
#include <util.hpp>

namespace p201
{
namespace systems
{
class combat : public system
{
public:
    using __base = system;

protected:
public:
    combat(class world& world) : __base(world)
    {
        /** @todo Revise this shit. */
        flag.set(components::character::flag);
        flag.set(components::physics::flag);
        flag.set(components::health::flag);
    }
    virtual ~combat() override = default;
    virtual void start() override;
    virtual void update(float dt) override;

    void on_attack_event(events::attack&);

    combat(const combat&) = delete;
    combat(combat&&)      = delete;
    combat& operator=(const combat&) = delete;
    combat& operator=(combat&&) = delete;
};
} // namespace systems
} // namespace p201
