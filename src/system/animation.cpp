

#include "animation.hpp"

#include "../__common.hpp"
#include "../entity.hpp"
#include "../entity_manager.hpp"
#include "../event.hpp"
#include "../util.hpp"
#include "../window.hpp"
#include "../world.hpp"

namespace p201
{
namespace systems
{
    void animation::start()
    {
        world.event_bus.subscribe(*this, &animation::on_animation_event);
    }
    void animation::update()
    {
        for (auto& ref_pair : __registered_entities)
        {
            auto& entity    = ref_pair.second.get();
            auto& animation = entity.component<components::animation>();
            auto& render    = entity.component<components::render>();

            auto& flipbook =
                world.sprite_manager.flipbook(render.family, animation.name);

            std::size_t delay = 1.0f / animation.fps * global::game_fps;
            ++animation.frame %= delay;
            if (!animation.frame) ++animation.index %= flipbook.frames();
            render.texture = flipbook.at(animation.index);
        }
    }
    void animation::on_animation_event(animation_event& event)
    {
        auto& animation = event.entity.component<components::animation>();
        animation.name  = event.name;
        animation.frame = 0;
        animation.index = 0;
    }
} // namespace systems
} // namespace p201
