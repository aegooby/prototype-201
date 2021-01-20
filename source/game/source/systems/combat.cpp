

#include "combat.hpp"

#include <__common.hpp>

namespace p201
{
namespace systems
{
void combat::start()
{
    world.event_manager.subscribe(*this, &combat::on_attack_event);
}
void combat::update(float dt)
{
    __base::update(dt);
    for (auto& id : __registered_entities)
    {
        auto& entity = world.entity(id);
        auto& health = entity.component<components::health>();
        /** @todo Add HUD system. */
        if (entity.flag.test(components::hud::flag))
        {
            const auto hpfactor = health.hp / health.max_hp;
            auto&      hb_main  = world.hud.healthbar.main;
            hb_main.rect.w      = hb_main.width * hpfactor;
            hb_main.srcrect.w   = hb_main.width * hpfactor;
        }
    }
}

void combat::on_attack_event(events::attack& event)
{
    /** @todo Implement. */
    (void)event;
}
} // namespace systems
} // namespace p201
