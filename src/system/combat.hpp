
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
class combat : public system
{
public:
    using __base = system;

protected:
public:
    combat(class world& world) : __base(world)
    {
        flag.set(components::health::flag);
    }
    virtual ~combat() = default;
    virtual void start() override;
    virtual void update(float dt) override;

    combat(const combat&) = delete;
    combat(combat&&)      = delete;
    combat& operator=(const combat&) = delete;
    combat& operator=(combat&&) = delete;
};
} // namespace systems
} // namespace p201
