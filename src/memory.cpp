
#include	"__common.hpp"
#include	"memory.hpp"

__attribute__((always_inline))
void*	operator new(std::size_t bytes)
{
	return ::operator new(bytes, td::memory::align_v);
}
__attribute__((always_inline))
void	operator delete(void* ptr) noexcept
{
	::operator delete(ptr, td::memory::align_v);
}
