
#pragma once
#include "character.hpp"

#include <__common.hpp>
#include <ecs.hpp>

namespace p201
{
namespace components
{
struct attack : public component
{
    using __base  = component;
    using manager = component_manager_template<components::attack>;

    static constexpr std::size_t flag = 9;

    px::shape* shape = nullptr;

    attack(entity::id_t entity) : __base(entity) { }
    virtual ~attack() override = default;

    void init([[maybe_unused]] px::scene& scene, character& character)
    {
        auto actor = character.controller->getActor();

        px::PxCapsuleGeometry capsule;
        character.shape->getCapsuleGeometry(capsule);

        auto material = px::sdk.main->createMaterial(0.0f, 0.0f, 0.0f);
        if (!material) throw std::runtime_error("Failed to create material");
        auto geometry = px::PxBoxGeometry(capsule.radius, capsule.radius,
                                          capsule.halfHeight + capsule.radius);
        shape = px::PxRigidActorExt::createExclusiveShape(*actor, geometry,
                                                          *material);
        shape->setFlag(px::PxShapeFlag::eSIMULATION_SHAPE, false);
        shape->setFlag(px::PxShapeFlag::eTRIGGER_SHAPE, true);

        auto position = /*px::coord **/ px::vector_3(100, 0, 0);

        shape->setLocalPose(px::PxTransform(position)); //, px::z_ctrl));
    }
};
} // namespace components
} // namespace p201