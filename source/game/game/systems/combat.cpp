

#include "combat.hpp"

#include <engine/__common.hpp>

namespace p201
{
namespace systems
{
void combat::start()
{
    world.event_manager.subscribe(*this, &combat::on_attack_event);
}
void combat::update(float dt)
{
    __base::update(dt);
    for (auto& id : __registered_entities)
    {
        auto& entity = world.entity(id);
        auto& health = entity.component<components::health>();
        P201_EVAL_DISCARD(health);
    }
}

void combat::init(components::attack& attack, components::character& character)
{
    auto actor = character.controller->getActor();

    px::PxCapsuleGeometry capsule;
    character.shape->getCapsuleGeometry(capsule);

    auto mat = px::sdk.main->createMaterial(0.0f, 0.0f, 0.0f);
    if (!mat) throw std::runtime_error("Failed to create material");
    auto geometry = px::PxBoxGeometry(capsule.radius, capsule.radius,
                                      capsule.halfHeight + capsule.radius);

    auto& shape = attack.shape;
    shape = px::PxRigidActorExt::createExclusiveShape(*actor, geometry, *mat);
    shape->setFlag(px::PxShapeFlag::eSIMULATION_SHAPE, false);
    shape->setFlag(px::PxShapeFlag::eTRIGGER_SHAPE, true);

    auto position = px::vector_3(100, 0, 0);

    shape->setLocalPose(px::PxTransform(position));
}

void combat::on_attack_event(events::attack& event)
{
    /** @todo Implement. */
    (void)event;
}
} // namespace systems
} // namespace p201
