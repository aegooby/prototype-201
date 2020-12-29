

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
        (void)render;
    }
}
} // namespace systems
} // namespace p201
