
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
    virtual ~allocator() = default;
    virtual void* allocate(size_t size, const char* typeName,
                           const char* filename, int line)
    {
        return operator new(size, std::align_val_t(PHYSX_MEM_ALIGN));
    }
    virtual void deallocate(void* ptr)
    {
        return operator delete(ptr, std::align_val_t(PHYSX_MEM_ALIGN));
    }
};
class error : public PxErrorCallback
{
public:
    virtual ~error() = default;
    virtual void reportError(PxErrorCode::Enum code, const char* message,
                             const char* file, int line)
    {
        std::clog << termcolor::bold << termcolor::red << "error "
                  << termcolor::reset << "(code " << std::size_t(code)
                  << "): " << message << std::endl;
    }
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
    PxSceneDesc desc;

public:
    PxScene* main = nullptr;
    scene(sdk& sdk) : desc(PxSceneDesc(sdk.main->getTolerancesScale()))
    {
        desc.gravity = PxVec3(0.0f, 0.0f, 0.0f);
        if (!desc.cpuDispatcher)
            desc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
        if (!desc.filterShader)
            desc.filterShader = PxDefaultSimulationFilterShader;
        main = sdk.main->createScene(desc);
        if (!main) throw std::runtime_error("Failed to initialize PhysX scene");

        if constexpr (debug)
        {
            using vparam = PxVisualizationParameter;
            main->setVisualizationParameter(vparam::eSCALE, 1.0f);
            main->setVisualizationParameter(vparam::eCOLLISION_SHAPES, 1.0f);
        }
    }
    ~scene()
    {
        if (main) main->release();
    }
};

class controller_manager
{
public:
    PxControllerManager* main = nullptr;

    controller_manager(scene& scene)
    {
        main = PxCreateControllerManager(*scene.main);
        main->setOverlapRecoveryModule(true);
    }
    ~controller_manager()
    {
        if (main) main->release();
    }
};

using actor       = PxActor;
using rigid_actor = PxRigidActor;
using controller  = PxController;
using vector_2    = PxVec2;
using vector_3    = PxVec3;
using vector_3ext = PxExtendedVec3;

inline class sdk  sdk;
inline const auto z_rotate = PxTransform(PxQuat(PxHalfPi, PxVec3(0, 1, 0)));
} // namespace px
} // namespace p201
