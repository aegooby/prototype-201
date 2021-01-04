
#include "memory.hpp"

#include "__common.hpp"

void* operator new(std::size_t bytes)
{
    return ::operator new(bytes, p201::memory::align_v);
}
void operator delete(void* ptr) noexcept
{
    ::operator delete(ptr, p201::memory::align_v);
}
