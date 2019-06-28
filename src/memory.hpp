
#pragma	once
#include	"__common.hpp"
#include	<new>
#include	<memory>
#include	<cstdlib>
#include	<cstring>

#define	__begin_ns_memory	namespace	memory {
#define	__end_ns_memory		}

__begin_ns_td
__begin_ns_memory

static constexpr size_t	align = (alignof(std::max_align_t) > 16 ? alignof(std::max_align_t) : 16);
static constexpr std::align_val_t	align_v = std::align_val_t(align);

__end_ns_memory
__end_ns_td


void*	operator new(std::size_t);
void	operator delete(void*) noexcept;

__begin_ns_td
__begin_ns_memory

class	__memory_private
{
private:
	inline static void*	allocate(size_t bytes, std::align_val_t align)
	{
		return operator new(bytes, align);
	}
	inline static void		deallocate(void* ptr, std::align_val_t align)
	{
		operator delete(ptr, align);
	}
public:
	template	<typename type>
	friend type*	allocate(type*&, size_t, std::align_val_t);
	template	<typename type>
	friend type*	allocate(type*&);
	template	<typename type>
	friend type*	allocate(type*&, size_t);
	template	<typename type>
	friend type*	allocate(type*&, std::align_val_t);
	template	<typename type>
	friend void		deallocate(type*&, std::align_val_t);
	template	<typename type>
	friend void		deallocate(type*&);
	
	__memory_private() = delete;
	__memory_private(const __memory_private&) = delete;
	__memory_private(__memory_private&&) = delete;
	__memory_private&	operator =(const __memory_private&) = delete;
	__memory_private&	operator =(__memory_private&&) = delete;
};

template	<typename type>
inline __attribute__((always_inline))
type* 	allocate(type* ptr, size_t count, std::align_val_t align)
{
	//	Allocation and assignment to parameter "ptr" is already done inside this
	//	function, but it returns "ptr" for ease of use.
	return static_cast<type*>(__memory_private::allocate(count * sizeof(type), align));
}
template	<typename type>
inline __attribute__((always_inline))
type* 	allocate(type*& ptr)
{
	ptr = static_cast<type*>(__memory_private::allocate(sizeof(type), td::memory::align_v));
	return ptr;
}
template	<typename type>
inline __attribute__((always_inline))
type* 	allocate(type*& ptr, size_t count)
{
	ptr = static_cast<type*>(__memory_private::allocate(count * sizeof(type), td::memory::align_v));
	return ptr;
}
template	<typename type>
inline __attribute__((always_inline))
type* 	allocate(type*& ptr, std::align_val_t align)
{
	ptr = static_cast<type*>(__memory_private::allocate(sizeof(type), align));
	return ptr;
}
template	<typename type, typename ... types>
inline __attribute__((always_inline))
type* 	construct(type* ptr, types&& ... args)
{
	//	Construction should always be done inside of a RAII container,
	//	and should always be implemented in sequential order.

	//	Conditional static_assert to improve error readibility when attempting
	//	to default-initialize a class with a deleted default constructor.
	if constexpr(!sizeof...(args))
		static_assert(std::is_default_constructible_v<type>);

	//	Placement-new on selected block of memory.
	//	Type "type" may need to be typecasted if working with nested containers.
	new(ptr) type(std::forward<types>(args)...);
	return ptr;
}
template	<typename type>
inline __attribute__((always_inline))
void 	destruct(type* ptr)
{
	//	Destructs in reverse order, which is why construct() should always be
	//	implemented in sequential order.
	ptr->~type();
}
template	<typename type>
inline __attribute__((always_inline))
void 	deallocate(type*& ptr, std::align_val_t align)
{
	//	Always call after destruct()
	__memory_private::deallocate((void*)const_cast<type*>(ptr), align);
	ptr = nullptr;
}
template	<typename type>
inline __attribute__((always_inline))
void 	deallocate(type*& ptr)
{
	__memory_private::deallocate((void*)const_cast<type*>(ptr), td::memory::align_v);
	ptr = nullptr;
}

__end_ns_memory
__end_ns_td
