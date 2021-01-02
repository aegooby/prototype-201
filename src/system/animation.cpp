

#include "animation.hpp"

#include "../__common.hpp"
#include "../entity.hpp"
#include "../entity_manager.hpp"
#include "../event.hpp"
#include "../util.hpp"
#include "../window.hpp"
#include "../world.hpp"
#include "render.hpp"

namespace p201
{
namespace systems
{
void animation::start()
{
    world.event_manager.subscribe(*this, &animation::on_animation_event);
}
void animation::update()
{
    auto& sprite_manager = world.system<systems::render>().sprite_manager;
    for (auto& id : __registered_entities)
    {
        auto& entity    = world.entity(id);
        auto& animation = entity.component<components::animation>();
        auto& render    = entity.component<components::render>();

        auto& flipbook = sprite_manager.flipbook(render.family, animation.name);

        if (!animation.fps) continue;
        std::size_t delay = 1.0f / animation.fps * global::game_fps;
        ++animation.frame %= delay;
        if (!animation.frame) ++animation.index %= flipbook.frames();
        render.texture = flipbook.at(animation.index);
    }
}
void animation::on_animation_event(events::animation& event)
{
    auto& animation = event.entity.component<components::animation>();
    animation.name  = event.name;
    animation.frame = 0;
    animation.index = 0;
}
} // namespace systems
} // namespace p201
