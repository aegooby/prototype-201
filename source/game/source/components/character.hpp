
#pragma once
#include <__common.hpp>
#include <ecs.hpp>

namespace p201
{
namespace components
{
struct character : public component
{
    using __base  = component;
    using manager = component_manager_template<components::character>;

    static constexpr std::size_t flag = 4;

    character(entity::id_t entity) : __base(entity) { }
    virtual ~character() override = default;

    px::controller* controller = nullptr;
    px::shape*      shape      = nullptr;

    vector_3 accel     = vector_3(0.0f, 0.0f, 0.0f);
    vector_3 velocity  = vector_3(0.0f, 0.0f, 0.0f);
    float    max_speed = 0.0f;
    float    friction  = 0.0f;
};
} // namespace components
} // namespace p201