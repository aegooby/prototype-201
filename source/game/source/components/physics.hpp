
#pragma once
#include <__common.hpp>
#include <ecs.hpp>

namespace p201
{
namespace components
{
struct physics : public component
{
    using __base  = component;
    using manager = component_manager_template<components::physics>;

    static constexpr std::size_t flag = 3;

    enum shape_types
    {
        undefined = 0,
        capsule   = 1,
        box       = 2,
    };

    bool        dynamic    = true;
    float       sf         = 0.0f;
    float       df         = 0.0f;
    float       e          = 0.0f;
    float       density    = 0.0f;
    shape_types shape_type = undefined;
    union shape_params
    {
        struct
        {
            float r;
            float hh;
        } capsule;
        struct
        {
            float hx;
            float hy;
            float hz;
        } box;
        shape_params()  = default;
        ~shape_params() = default;
    } shape_param;

    px::rigid_actor* actor = nullptr;
    px::shape*       shape = nullptr;

    physics(entity::id_t entity) : __base(entity) { }
    virtual ~physics() override = default;
};
} // namespace components
} // namespace p201