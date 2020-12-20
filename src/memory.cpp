
#include "memory.hpp"

#include "__common.hpp"

__attribute__((always_inline)) void* operator new(std::size_t bytes)
{
    return ::operator new(bytes, p201::memory::align_v);
}
__attribute__((always_inline)) void operator delete(void* ptr) noexcept
{
    ::operator delete(ptr, p201::memory::align_v);
}
