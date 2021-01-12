
#pragma once

/* clang-format off */
#include "__common.hpp"
/* clang-format on */

#include "PxConfig.h"
#include "PxPhysicsAPI.h"
#include "termcolor.hpp"

#include <new>

#define PHYSX_PVD_HOST  "localhost"
#define PHYSX_MEM_ALIGN 16

namespace p201
{

namespace px
{
using namespace physx;

class allocator : public PxAllocatorCallback
{
public:
    virtual ~allocator() override = default;
    virtual void* allocate(size_t size, const char* typeName,
                           const char* filename, int line) override
    {
        (void)typeName;
        (void)filename;
        (void)line;
        return operator new(size, std::align_val_t(PHYSX_MEM_ALIGN));
    }
    virtual void deallocate(void* ptr) override
    {
        return operator delete(ptr, std::align_val_t(PHYSX_MEM_ALIGN));
    }
};
class error : public PxErrorCallback
{
public:
    virtual ~error() override = default;
    virtual void reportError(PxErrorCode::Enum code, const char* message,
                             const char* file, int line) override
    {
        (void)file;
        (void)line;
        std::clog << termcolor::bold << termcolor::red << "error "
                  << termcolor::reset << "(code " << std::size_t(code)
                  << "): " << message << std::endl;
    }
};

/** @todo Finish */
class callback : public PxSimulationEventCallback
{
private:
    class world& world;

public:
    callback(class world& world) : world(world) { }
    virtual void onConstraintBreak(PxConstraintInfo* constraints,
                                   PxU32             count) override;
    virtual void onWake(PxActor** actors, PxU32 count) override;
    virtual void onSleep(PxActor** actors, PxU32 count) override;
    virtual void onContact(const PxContactPairHeader& pairHeader,
                           const PxContactPair* pairs, PxU32 nbPairs) override;
    virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) override;
    virtual void onAdvance(const PxRigidBody* const* bodyBuffer,
                           const PxTransform*        poseBuffer,
                           const PxU32               count) override;
    virtual ~callback() override = default;
};

class sdk
{
private:
    px::error         error;
    px::allocator     alloc;
    PxTolerancesScale scale = PxTolerancesScale();

public:
    struct pvd
    {
        PxPvd*          main      = nullptr;
        PxPvdTransport* transport = nullptr;
    } pvd;
    PxFoundation* foundation = nullptr;
    PxPhysics*    main       = nullptr;
    PxCooking*    cooking    = nullptr;

    sdk()
    {
        foundation = PxCreateFoundation(PX_PHYSICS_VERSION, alloc, error);
        if (!foundation)
            throw std::runtime_error("Failed to initialize PhysX foundation");
        pvd.main = PxCreatePvd(*foundation);
        if (!pvd.main)
            throw std::runtime_error("Failed to initialize PhysX PVD");
        pvd.transport =
            PxDefaultPvdSocketTransportCreate(PHYSX_PVD_HOST, 5425, 10);
        pvd.main->connect(*pvd.transport, PxPvdInstrumentationFlag::eALL);
        main = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, scale, true,
                               pvd.main);
        if (!main) throw std::runtime_error("Failed to initialize PhysX SDK");
        cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation,
                                  PxCookingParams(scale));
        if (!cooking)
            throw std::runtime_error("Failed to initialize PhysX cooking");
    }
    ~sdk()
    {
        if (cooking) cooking->release();
        if (main) main->release();
        if (foundation) foundation->release();
    }
};
class scene
{
private:
    class callback callback;
    PxSceneDesc    desc;

public:
    PxScene*             main               = nullptr;
    PxControllerManager* controller_manager = nullptr;
    scene(class world& world, class sdk& sdk)
        : callback(world), desc(PxSceneDesc(sdk.main->getTolerancesScale()))
    {
        desc.gravity = PxVec3(0.0f, 0.0f, 0.0f);
        if (!desc.cpuDispatcher)
            desc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
        if (!desc.filterShader)
            desc.filterShader = PxDefaultSimulationFilterShader;
        desc.simulationEventCallback = &callback;

        main = sdk.main->createScene(desc);
        if (!main) throw std::runtime_error("Failed to initialize PhysX scene");

        if constexpr (debug)
        {
            using vparam = PxVisualizationParameter;
            main->setVisualizationParameter(vparam::eSCALE, 1.0f);
            main->setVisualizationParameter(vparam::eCOLLISION_SHAPES, 1.0f);
            main->setVisualizationParameter(vparam::eJOINT_LIMITS, 1.0f);
        }

        controller_manager = PxCreateControllerManager(*main);
        controller_manager->setOverlapRecoveryModule(true);
    }
    ~scene()
    {
        if (controller_manager) controller_manager->release();
        if (main) main->release();
    }
};

using actor       = PxActor;
using rigid_actor = PxRigidActor;
using shape       = PxShape;
using aggregate   = PxAggregate;
using controller  = PxController;
using vector_2    = PxVec2;
using vector_3    = PxVec3;
using vector_3ext = PxExtendedVec3;

inline class sdk sdk;
} // namespace px
} // namespace p201
