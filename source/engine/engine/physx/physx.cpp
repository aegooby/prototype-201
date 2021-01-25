
#include "physx.hpp"

#include "../core.hpp"
#include "../ecs.hpp"
#include "../event.hpp"

#include <__common.hpp>

namespace p201
{
namespace px
{
void callback::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)
{
    (void)constraints;
    (void)count;
}
void callback::onWake(PxActor** actors, PxU32 count)
{
    (void)actors;
    (void)count;
}
void callback::onSleep(PxActor** actors, PxU32 count)
{
    (void)actors;
    (void)count;
}
void callback::onContact(const PxContactPairHeader& pairHeader,
                         const PxContactPair* pairs, PxU32 nbPairs)
{
    (void)pairHeader;
    (void)pairs;
    (void)nbPairs;
}
void callback::bind_on_trigger(
    const std::function<void(PxTriggerPair*, PxU32)>& function)
{
    on_trigger = function;
}
void callback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
    /** @todo Add function binding. */
    on_trigger(pairs, count);
    // for (std::size_t i = 0; i < count; ++i)
    // {
    //     auto& attacker = *(entity*)pairs[i].triggerActor->userData;
    //     auto& victim   = *(entity*)pairs[i].otherActor->userData;
    //     world.event_manager.publish<events::attack>(attacker, victim);
    // }
}
void callback::onAdvance(const PxRigidBody* const* bodyBuffer,
                         const PxTransform* poseBuffer, const PxU32 count)
{
    (void)bodyBuffer;
    (void)poseBuffer;
    (void)count;
}
} // namespace px
} // namespace p201