
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
class allocator : public physx::PxAllocatorCallback
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
class error : public physx::PxErrorCallback
{
public:
    virtual ~error() = default;
    virtual void reportError(physx::PxErrorCode::Enum code, const char* message,
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
    px::error                error;
    px::allocator            alloc;
    physx::PxTolerancesScale scale = physx::PxTolerancesScale();

public:
    struct pvd
    {
        physx::PxPvd*          main      = nullptr;
        physx::PxPvdTransport* transport = nullptr;
    } pvd;
    physx::PxFoundation* foundation = nullptr;
    physx::PxPhysics*    main       = nullptr;
    physx::PxCooking*    cooking    = nullptr;

    sdk()
    {
        foundation = PxCreateFoundation(PX_PHYSICS_VERSION, alloc, error);
        if (!foundation)
            throw std::runtime_error("Failed to initialize PhysX foundation");
        pvd.main = physx::PxCreatePvd(*foundation);
        if (!pvd.main)
            throw std::runtime_error("Failed to initialize PhysX PVD");
        pvd.transport =
            physx::PxDefaultPvdSocketTransportCreate(PHYSX_PVD_HOST, 5425, 10);
        pvd.main->connect(*pvd.transport,
                          physx::PxPvdInstrumentationFlag::eALL);
        main = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, scale, true,
                               pvd.main);
        if (!main) throw std::runtime_error("Failed to initialize PhysX SDK");
        cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation,
                                  physx::PxCookingParams(scale));
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
    physx::PxSceneDesc desc;

public:
    physx::PxScene* main = nullptr;
    scene(sdk& sdk) : desc(physx::PxSceneDesc(sdk.main->getTolerancesScale()))
    {
        desc.gravity = physx::PxVec3(0.0f, 0.0f, 0.0f);
        if (!desc.cpuDispatcher)
            desc.cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(1);
        if (!desc.filterShader)
            desc.filterShader = physx::PxDefaultSimulationFilterShader;
        main = sdk.main->createScene(desc);
        if (!main) throw std::runtime_error("Failed to initialize PhysX scene");

        using vparam = physx::PxVisualizationParameter;
        main->setVisualizationParameter(vparam::eSCALE, 1.0f);
        main->setVisualizationParameter(vparam::eCOLLISION_SHAPES, 1.0f);
    }
    ~scene()
    {
        if (main) main->release();
    }
};

class controller_manager
{
public:
    physx::PxControllerManager* main = nullptr;

    controller_manager(scene& scene)
    {
        main = PxCreateControllerManager(*scene.main);
    }
    ~controller_manager()
    {
        if (main) main->release();
    }
};

using actor       = physx::PxActor;
using rigid_actor = physx::PxRigidActor;
using controller  = physx::PxController;
using vector_2    = physx::PxVec2;
using vector_3    = physx::PxVec3;

inline rigid_actor* rigid(physx::PxActor* actor)
{
    return actor->is<physx::PxRigidActor>()
               ?: throw std::runtime_error("Bad PhysX cast");
}

inline class sdk sdk;
} // namespace px
} // namespace p201
