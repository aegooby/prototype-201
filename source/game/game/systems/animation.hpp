
#pragma once
#include "../components.hpp"
#include "../events.hpp"

#include <engine/__common.hpp>
#include <engine/core.hpp>
#include <engine/ecs.hpp>
#include <engine/event.hpp>
#include <engine/util.hpp>

namespace p201
{
namespace systems
{
class animation : public system
{
public:
    using __base = system;

protected:
public:
    animation(class world& world) : __base(world)
    {
        flag.set(components::render::flag);
        flag.set(components::animation::flag);
    }
    virtual ~animation() override = default;
    virtual void start() override;
    virtual void update(float dt) override;

    void on_animation_event(events::animation&);

    animation(const animation&) = delete;
    animation(animation&&)      = delete;
    animation& operator=(const animation&) = delete;
    animation& operator=(animation&&) = delete;
};
} // namespace systems
} // namespace p201
