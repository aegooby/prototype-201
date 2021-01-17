
#include "animation.hpp"

#include <__common.hpp>
#include <asset.hpp>

namespace p201
{
namespace systems
{
void animation::start()
{
    world.event_manager.subscribe(*this, &animation::on_animation_event);
}
void animation::update(float dt)
{
    __base::update(dt);
    const auto& sprite_manager = world.sprite_manager;
    for (auto& id : __registered_entities)
    {
        auto& entity    = world.entity(id);
        auto& animation = entity.component<components::animation>();
        auto& render    = entity.component<components::render>();

        const auto& flipbook =
            sprite_manager.flipbook(render.family, animation.name);

        if (animation.fps)
        {
            std::size_t delay = 1.0f / animation.fps * engine::dt_factor;
            ++animation.frame %= delay;
            if (!animation.frame) ++animation.index %= flipbook.frames();
            render.texture = flipbook.at(animation.index);
        }
    }
}
void animation::on_animation_event(events::animation& event)
{
    auto& animation = event.entity.component<components::animation>();
    if (animation.name != event.name)
    {
        animation.name  = event.name;
        animation.frame = 0;
        animation.index = 0;
    }
}
} // namespace systems
} // namespace p201
