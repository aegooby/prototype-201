
#pragma once
#include <__common.hpp>
#include <ecs.hpp>

namespace p201
{
namespace components
{
struct health : public component
{
    using __base  = component;
    using manager = component_manager_template<components::health>;

    static constexpr std::size_t flag = 8;

    float hp         = 0.0f;
    float max_hp     = 0.0f;
    float shield     = 0.0f;
    float max_shield = 0.0f;

    health(entity::id_t entity) : __base(entity) { }
    virtual ~health() override = default;
};
} // namespace components
} // namespace p201