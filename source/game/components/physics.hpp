
#pragma once
#include "../../__common.hpp"
#include "../../ecs.hpp"

namespace p201
{
namespace components
{
struct physics : public component
{
    using __base  = component;
    using manager = component_manager_template<components::physics>;

    static constexpr std::size_t flag = 3;

    enum shape_type : std::size_t
    {
        undefined = 0,
        capsule   = 1,
        box       = 2,
    };

    bool       dynamic    = true;
    float      sf         = 0.0f;
    float      df         = 0.0f;
    float      e          = 0.0f;
    float      density    = 0.0f;
    shape_type shape_type = undefined;
    union shape_param
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
        shape_param()  = default;
        ~shape_param() = default;
    } shape_params;

    px::rigid_actor* actor = nullptr;
    px::shape*       shape = nullptr;

    physics(std::size_t entity) : __base(entity) { }
    virtual ~physics() override = default;

    void init(px::scene& scene)
    {
        auto material = px::sdk.main->createMaterial(sf, df, e);
        if (!material) throw std::runtime_error("Failed to create material");
        auto transform = px::PxTransform(px::PxVec3(0, 0, 0));
        auto create    = [this, &transform,
                       &material](const auto& geometry) -> px::rigid_actor*
        {
            if (dynamic)
                return px::PxCreateDynamic(*px::sdk.main, transform, geometry,
                                           *material, density);
            else
                return px::PxCreateStatic(*px::sdk.main, transform, geometry,
                                          *material);
        };
        switch (shape_type)
        {
            case capsule:
            {
                actor = create(px::PxCapsuleGeometry(shape_params.capsule.r,
                                                     shape_params.capsule.hh));
                break;
            }
            case box:
            {
                actor = create(px::PxBoxGeometry(shape_params.box.hx,
                                                 shape_params.box.hy,
                                                 shape_params.box.hz));
                break;
            }
            default:
                break;
        }
        scene.main->addActor(*actor);
        actor->userData = &entity;
        actor->getShapes(&shape, 1);
    }
};
} // namespace components
} // namespace p201