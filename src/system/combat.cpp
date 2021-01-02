

#include "combat.hpp"

#include "../__common.hpp"
#include "../entity.hpp"
#include "../event.hpp"
#include "../util.hpp"
#include "../window.hpp"
#include "../world.hpp"
#include "render.hpp"

namespace p201
{
namespace systems
{
void combat::start() { }
void combat::update()
{
    for (auto& id : __registered_entities)
    {
        auto& entity = world.entity(id);
        auto& health = entity.component<components::health>();
        if (entity.flag.test(components::hud::flag))
        {
            const auto hpfactor = health.hp / health.max_hp;
            auto&      hb_main  = world.hud.healthbar.main;
            hb_main.rect.w      = hb_main.width * hpfactor;
            hb_main.srcrect.w   = hb_main.width * hpfactor;
        }
    }
}
} // namespace systems
} // namespace p201
