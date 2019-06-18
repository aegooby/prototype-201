
#pragma	once
#include	"../__common.hpp"
#include	"../memory.hpp"

__begin_ns_td

template	<typename vtype, size_t __size>
class array
{
public:
	using value_type = vtype;
	using reference	= value_type&;
	using rvalue_reference = value_type&&;
	using const_reference = const value_type&;
	using iterator = value_type*;
	using const_iterator = const value_type*;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using data_pointer = value_type*;
	using const__data_pointer = const value_type*;
	using size_type = size_t;
	using difference_type = std::ptrdiff_t;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using self_type = array<value_type, __size>;
	using self_reference = self_type&;
	using const_self_reference = const self_type&;
	using self_rvalue_reference =self_type&&;
	
	friend class	st_array<value_type, __size>;
	friend class	array<value_type, __size>;
protected:
	value_type*	__data = nullptr;
private:
	inline __attribute__((always_inline))
	void	allocate(size_type size)
	{
		if (size > std::numeric_limits<difference_type>::max())
			throw std::length_error("td::Array: size is too large");
		__data = memory::allocate(__data, size);
	}
	template	<class ... types>
	inline __attribute__((always_inline))
	void	construct(size_type offset, types&& ... args)
	{
		memory::construct(iterator(__data) + offset, std::forward<types>(args)...);
	}
	inline __attribute__((always_inline))
	void	destruct(size_type offset)
	{
		memory::destruct(iterator(__data) + offset);
	}
	inline __attribute__((always_inline))
	void	deallocate()
	{
		if (__data)
			memory::deallocate(__data);
	}
public:
	template	<class ... types>
	constexpr array(types&& ... args)
	{
		if constexpr(!sizeof...(args))
		{
			static_assert(std::is_default_constructible_v<value_type>);
		}
		this->allocate(__size > 0 ? __size : 1);
		for (size_t i = 0; i < __size; ++i)
			this->construct(i, std::forward<types>(args)...);
		if constexpr(!sizeof...(args))
		{
			this->fill(value_type());
		}
	}
	~array()
	{
		for (size_t i = __size - 1; i + 1 >= 1; --i)
			this->destruct(i);
		this->deallocate();
	}
	array(const_self_reference other)
	{
		this->allocate(__size > 0 ? __size : 1);
		memcpy(__data, other.__data, (__size > 0 ? __size : 1) * sizeof(value_type));
	}
	array(self_rvalue_reference other)
	{
		__data = other.__data;
		other.__data = nullptr;
	}
	array(const st_array<value_type, __size>&);
	array(st_array<value_type, __size>&&);
	inline __attribute__((always_inline))
	self_reference	operator =(const_self_reference other) noexcept
	{
		memcpy(__data, other.__data, (__size > 0 ? __size : 1) * sizeof(value_type));
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator =(self_rvalue_reference other) noexcept
	{
		memcpy(__data, other.__data, (__size > 0 ? __size : 1) * sizeof(value_type));
		return *this;
	}
	self_reference	operator =(const st_array<value_type, __size>&);
	self_reference	operator =(st_array<value_type, __size>&&);
	array(const std::initializer_list<value_type>& list)
	{
		if (list.size() != __size && !std::is_default_constructible_v<value_type>)
			throw std::runtime_error("td::Array: Initializer list leaves elements unininitialized");
		if (list.size() > __size)
			throw std::overflow_error("td::Array: Initializer list is larger than array");
		this->allocate(__size > 0 ? __size : 1);
		if (!list.size())
			memset(__data, 0, data_size());
		for (size_type offset = 0; offset < list.size(); ++offset)
		{
			this->construct(offset, *(iterator(list.begin()) + offset));
		}
	}
	inline __attribute__((always_inline))
	self_reference	operator =(const std::initializer_list<value_type>& list)
	{
		if (list.size() > __size)
			throw std::overflow_error("td::Array: Initializer list is larger than array");
		if (!list.size())
			memset(__data, 0, data_size());
		for (size_type offset = 0; offset < list.size(); ++offset)
		{
			*(iterator(__data) + offset) = *(iterator(list.begin()) + offset);
		}
		return *this;
	}
	inline __attribute__((always_inline))
	pointer	data() noexcept	{ return __data; }
	inline __attribute__((always_inline))
	const pointer	data() const noexcept	{ return __data; }
	inline __attribute__((always_inline))
	constexpr reference	at(size_type index)
	{
		if (index >= __size)
			throw std::out_of_range("td::Array::at: Element is out of range");
		return __data[index];
	}
	inline __attribute__((always_inline))
	constexpr const_reference	at(size_type index) const
	{
		if (index >= __size)
			throw std::out_of_range("td::Array::at: Element is out of range");
		return __data[index];
	}
	inline __attribute__((always_inline))
	constexpr reference		operator [](size_type index)
	{
		if (index >= __size)
			throw std::out_of_range("td::Array::at: Element is out of range");
		return __data[index];
	}
	inline __attribute__((always_inline))
	constexpr const_reference	operator [](size_type index) const
	{
		if (index >= __size)
			throw std::out_of_range("td::Array::at: Element is out of range");
		return __data[index];
	}
	inline __attribute__((always_inline))
	constexpr reference		front()
	{
		return *__data;
	}
	inline __attribute__((always_inline))
	constexpr const_reference	front() const
	{
		return *__data;
	}
	inline __attribute__((always_inline))
	constexpr reference		back()
	{
		return *(__data + (__size > 0 ? __size - 1 : 0));
	}
	inline __attribute__((always_inline))
	constexpr const_reference	back() const
	{
		return *(__data + (__size > 0 ? __size - 1 : 0));
	}

	inline __attribute__((always_inline))
	constexpr iterator	begin()
	{
		return iterator(__data);
	}
	inline __attribute__((always_inline))
	constexpr const_iterator	begin() const
	{
		return const_iterator(__data);
	}
	inline __attribute__((always_inline))
	constexpr const_iterator	cbegin() const
	{
		return const_iterator(__data);
	}
	inline __attribute__((always_inline))
	constexpr iterator	end()
	{
		return iterator(__data + __size);
	}
	inline __attribute__((always_inline))
	constexpr const_iterator	end() const
	{
		return const_iterator(__data + __size);
	}
	inline __attribute__((always_inline))
	constexpr const_iterator	cend() const
	{
		return const_iterator(__data + __size);
	}

	inline __attribute__((always_inline))
	constexpr reverse_iterator	rbegin()
	{
		return reverse_iterator(__data);
	}
	inline __attribute__((always_inline))
	constexpr const_reverse_iterator	rbegin() const
	{
		return const_reverse_iterator(__data);
	}
	inline __attribute__((always_inline))
	constexpr const_reverse_iterator	crbegin() const
	{
		return const_reverse_iterator(__data);
	}
	inline __attribute__((always_inline))
	constexpr reverse_iterator	rend()
	{
		return reverse_iterator(__data + __size);
	}
	inline __attribute__((always_inline))
	constexpr const_reverse_iterator	rend() const
	{
		return const_reverse_iterator(__data + __size);
	}
	inline __attribute__((always_inline))
	constexpr const_reverse_iterator	crend() const
	{
		return const_reverse_iterator(__data + __size);
	}

	inline __attribute__((always_inline))
	constexpr bool	empty() const noexcept
	{
		return (!bool(__size));
	}
	inline __attribute__((always_inline))
	constexpr size_type	size() const noexcept
	{
		return __size;
	}
	inline __attribute__((always_inline))
	constexpr size_type	elem_size() const noexcept
	{
		return sizeof(value_type);
	}
	inline __attribute__((always_inline))
	constexpr size_type	data_size() const noexcept
	{
		return sizeof(value_type) * __size;
	}
	inline __attribute__((always_inline))
	void	fill(const_reference value)
	{
		for (auto& i : *this)
			i = value;
	}
};

__end_ns_td
