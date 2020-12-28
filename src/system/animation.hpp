
#pragma once
#include "../__common.hpp"
#include "../entity.hpp"
#include "../event.hpp"
#include "../exception.hpp"
#include "../sprite.hpp"
#include "../window.hpp"
#include "system.hpp"

#include <unordered_map>

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
            flag.set(component::flag::render);
            flag.set(component::flag::animation);
        }
        virtual ~animation() = default;
        virtual void start() override;
        virtual void update() override;

        void on_animation_event(animation_event&);

        //	Preventing copying and moving
        animation(const animation&) = delete;
        animation(animation&&)      = delete;
        animation& operator=(const animation&) = delete;
        animation& operator=(animation&&) = delete;
    };
} // namespace systems
} // namespace p201
