
#include "collision.hpp"

#include "../__common.hpp"
#include "../entity_manager.hpp"
#include "../event.hpp"
#include "../world.hpp"

namespace p201
{
namespace systems
{
    void collision::start() { }
    void collision::update()
    {
        for (auto& entity : __registered_entities)
        {
            auto& transform =
                entity.second.get().component<transform_component>();
            auto& collision =
                entity.second.get().component<collision_component>();
            (void)transform;
            (void)collision;
        }
    }
} // namespace systems
} // namespace p201
