

#include "camera.hpp"

#include "../__common.hpp"
#include "../entity.hpp"
#include "../event.hpp"
#include "../util.hpp"
#include "../window.hpp"
#include "../world.hpp"

namespace p201
{
namespace systems
{
void camera::start() { }
void camera::update()
{
    for (auto& ref_pair : __registered_entities)
    {
        auto&       entity = ref_pair.second.get();
        const auto& render = entity.component<components::render>();
        if (!world.camera.active) world.camera.active = true;
        world.camera.center = util::center(render.rect);
    }
}
} // namespace systems
} // namespace p201