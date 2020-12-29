
#pragma once
#include "../__common.hpp"
#include "../entity.hpp"
#include "../event.hpp"
#include "../sprite.hpp"
#include "../window.hpp"
#include "system.hpp"

#include <unordered_map>

namespace p201
{
namespace systems
{
    class camera : public system
    {
    public:
        using __base = system;

    protected:
    public:
        camera(class world& world) : __base(world)
        {
            flag.set(components::render::flag);
            flag.set(components::camera::flag);
        }
        virtual ~camera() = default;
        virtual void start() override;
        virtual void update() override;

        void on_animation_event(events::animation&);

        //	Preventing copying and moving
        camera(const camera&) = delete;
        camera(camera&&)      = delete;
        camera& operator=(const camera&) = delete;
        camera& operator=(camera&&) = delete;
    };
} // namespace systems
} // namespace p201
