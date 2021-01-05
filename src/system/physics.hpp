
#pragma once
#include "../__common.hpp"
#include "../component.hpp"
#include "../entity.hpp"
#include "../event.hpp"
#include "system.hpp"

namespace p201
{
namespace systems
{
class physics : public system
{
public:
    using __base = system;

    physics(class world& world) : __base(world)
    {
        flag.set(components::transform::flag);
        flag.set(components::physics::flag);
    }
    virtual ~physics() = default;
    virtual void start() override;
    virtual void update(float dt) override;

    std::tuple<vector_3, vector_3> impulse(entity& entity1, entity& entity2);
    void                           collision_resolution(std::size_t id);

    void collision_resolution(entity& entity1, entity& entity2);
};
} // namespace systems
} // namespace p201
