
#pragma once

/* clang-format off */
#include "__common.hpp"
/* clang-format on */

#include "PxConfig.h"
#include "PxPhysicsAPI.h"

#include <new>

#define PHYSX_PVD_HOST  "127.0.0.1"
#define PHYSX_MEM_ALIGN 16

namespace p201
{
class PxAlignedNewCallback : public physx::PxAllocatorCallback
{
public:
    virtual ~PxAlignedNewCallback() { }
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
} // namespace p201
