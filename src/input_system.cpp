
#include "input_system.hpp"

#include "__common.hpp"
#include "entity.hpp"
#include "event_bus.hpp"
#include "sprite.hpp"
#include "world.hpp"

namespace p201
{

void input_system::start()
{
    world.event_bus.subscribe(*this,
                              &input_system::on_animation_complete_event);
}
void input_system::update()
{
    auto& keyboard = world.keyboard;
    auto& mouse    = world.mouse;
    for (auto& entity : __registered_entities)
    { auto& input = entity.second.get().component<input_component>(); }
}
void input_system::on_animation_complete_event(animation_complete_event& event)
{
    auto& input  = event.entity.component<input_component>();
    auto& render = event.entity.component<render_component>();
}

} // namespace p201
