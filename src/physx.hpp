
#pragma once

/* clang-format off */
#include "__common.hpp"
/* clang-format on */

#include "PxConfig.h"
#include "PxPhysicsAPI.h"
#include "util.hpp"

#include <new>

#define PHYSX_PVD_HOST  "127.0.0.1"
#define PHYSX_MEM_ALIGN 16

namespace p201
{
class physx_allocator : public physx::PxAllocatorCallback
{
public:
    virtual ~physx_allocator() = default;
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

class physx_error : public physx::PxErrorCallback
{
public:
    virtual ~physx_error() = default;
    virtual void reportError(physx::PxErrorCode::Enum code, const char* message,
                             const char* file, int line)
    {
        std::clog << util::tc::bold << util::tc::cyan << "<PhysX>"
                  << util::tc::red << " error" << util::tc::reset << "(code "
                  << std::size_t(code) << "): " << message << std::endl;
    }
};
} // namespace p201
