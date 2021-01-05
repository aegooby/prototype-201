
#pragma once
#include "../__common.hpp"
#include "../entity.hpp"
#include "../event.hpp"
#include "../window.hpp"
#include "system.hpp"

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
    virtual ~animation() = default;
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
