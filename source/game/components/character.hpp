
#pragma once
#include "../../__common.hpp"
#include "../../ecs.hpp"
#include "physics.hpp"

namespace p201
{
namespace components
{
struct character : public component
{
    using __base = component;
    using manager = component_manager_template<components::character>;

    static constexpr std::size_t flag = 4;

    character(std::size_t entity) : __base(entity) { }
    virtual ~character() override = default;

    px::controller* controller = nullptr;
    px::shape*      shape      = nullptr;

    vector_3 accel     = vector_3(0.0f, 0.0f, 0.0f);
    vector_3 velocity  = vector_3(0.0f, 0.0f, 0.0f);
    float    max_speed = 0.0f;
    float    friction  = 0.0f;

    void init(px::scene& scene, physics& physics)
    {
        px::PxCapsuleControllerDesc desc;

        auto material =
            px::sdk.main->createMaterial(physics.sf, physics.df, physics.e);
        desc.radius = physics.shape_params.capsule.r;
        desc.height = physics.shape_params.capsule.hh * 2.0f;
        /** @todo Temporary values */
        desc.stepOffset  = 0.01f;
        desc.density     = physics.density;
        desc.material    = material;
        desc.upDirection = px::vector_3(0, 0, 1);
        desc.position    = px::vector_3ext(0, 0, 0);

        controller    = scene.controller_manager->createController(desc);
        physics.actor = controller->getActor();
        physics.actor->userData = &entity;
        controller->setUserData(&physics);

        physics.actor->getShapes(&physics.shape, 1);
        shape = physics.shape;

        physics.shape->setLocalPose(px::transform(px::z_ctrl));
    }
};
} // namespace components
}