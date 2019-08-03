
#pragma	once
#include	"../__common.hpp"
#include	"st_array_base.hpp"
#include	"../memory.hpp"

__begin_ns_td

template	<typename __value_type, size_t rows, size_t columns>
class	table
{
public:
	using value_type = __value_type;
	using reference = value_type&;
	using rvalue_reference = value_type&&;
	using const_reference = const value_type&;
	using array_type = st_array<value_type, columns>;
	using array_reference = st_array<value_type, columns>&;
	using const_array_reference = const st_array<value_type, columns>&;
	using iterator = value_type*;
	using const_iterator = const value_type*;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using array_pointer = st_array<value_type, columns>*;
	using const_array_pointer = const st_array<value_type, columns>*;
	using data_pointer = st_array<value_type, columns>*;
	using const__data_pointer = const st_array<value_type, columns>*;
	using size_type = size_t;
	using difference_type = std::ptrdiff_t;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using self_type = table<value_type, rows, columns>;
	using self_reference = self_type&;
	using const_self_reference = const self_type&;
	using self_rvalue_reference = self_type&&;

	friend class	table<value_type, rows, columns>;
	friend class	st_table<value_type, rows, columns>;
	friend class	st_array<value_type, columns>;
protected:
	st_array<value_type, columns>*	__data = nullptr;
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
	constexpr table(types&& ... args)
	{
		if constexpr(!sizeof...(args))
		{
			static_assert(std::is_default_constructible_v<value_type>);
		}
		this->allocate(rows);
		for (size_t i = 0; i < rows * columns; ++i)
			this->construct(i, std::forward<types>(args)...);
		if constexpr(!sizeof...(args))
		{
			this->fill(value_type());
		}
	}
	~table()
	{
		for (size_t i = rows * columns - 1; i + 1 >= 1; --i)
			this->destruct(i);
		this->deallocate();
	}
	table(const_self_reference other)
	{
		this->allocate(rows);
		memcpy(__data, other.__data, (rows) * sizeof(st_array<value_type, columns>));
	}
	table(self_rvalue_reference other)
	{
		__data = other.__data;
		other.__data = nullptr;
	}
	table(const st_table<value_type, rows, columns>&);
	table(st_table<value_type, rows, columns>&&);
	inline __attribute__((always_inline))
	self_reference	operator =(const_self_reference other)
	{
		memcpy(__data, other.__data, (rows) * sizeof(st_array<value_type, columns>));
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator =(self_rvalue_reference other)
	{
		memcpy(__data, other.__data, (rows) * sizeof(st_array<value_type, columns>));
		return *this;
	}
	self_reference	operator =(const st_table<value_type, rows, columns>&);
	self_reference	operator =(st_table<value_type, rows, columns>&&);
	table(const std::initializer_list<value_type>& list)
	{
		if (list.size() != rows * columns && !std::is_default_constructible_v<value_type>)
			throw std::runtime_error("td::Array: Initializer list leaves elements unininitialized");
		if (list.size() > columns * rows)
			throw std::overflow_error("td::Array: Initializer list is larger than array");
		this->allocate(rows);
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
		if (list.size() > columns * rows)
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
	pointer	data() noexcept	{ return __data->data(); }
	inline __attribute__((always_inline))
	const_pointer	data() const noexcept	{ return __data->data(); }
	inline __attribute__((always_inline))
	constexpr reference	at(size_type column, size_type row)
	{
		if (column >= rows || row >= columns)
			throw std::out_of_range("td::Array::at: Element is out of range");
		return __data[column][row];
	}
	inline __attribute__((always_inline))
	constexpr const_reference	at(size_type column, size_type row) const
	{
		if (column >= rows || row >= columns)
			throw std::out_of_range("td::Array::at: Element is out of range");
		return __data[column][row];
	}
	inline __attribute__((always_inline))
	constexpr array_reference	at(size_type index)
	{
		if (index >= rows)
			throw std::out_of_range("td::Array::at: Element is out of range");
		return __data[index];
	}
	inline __attribute__((always_inline))
	constexpr const_array_reference	at(size_type index) const
	{
		if (index >= rows)
			throw std::out_of_range("td::Array::at: Element is out of range");
		return __data[index];
	}
	inline __attribute__((always_inline))
	constexpr array_reference		operator [](size_type index)
	{
		if (index >= rows)
			throw std::out_of_range("td::Array::at: Element is out of range");
		return __data[index];
	}
	inline __attribute__((always_inline))
	constexpr const_array_reference	operator [](size_type index) const
	{
		if (index >= rows)
			throw std::out_of_range("td::Array::at: Element is out of range");
		return __data[index];
	}

	inline __attribute__((always_inline))
	constexpr reference		front()
	{
		return *(pointer(__data));
	}
	inline __attribute__((always_inline))
	constexpr const_reference	front() const
	{
		return *(const_pointer(__data));
	}
	inline __attribute__((always_inline))
	constexpr reference		back()
	{
		return *(pointer(__data) + ((rows * columns) > 0 ? (rows * columns) - 1 : 0));
	}
	inline __attribute__((always_inline))
	constexpr const_reference	back() const
	{
		return *(const_pointer(__data) + ((rows * columns) > 0 ? (rows * columns) - 1 : 0));
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
		return iterator(__data) + rows * columns;
	}
	inline __attribute__((always_inline))
	constexpr const_iterator	end() const
	{
		return const_iterator(__data) + rows * columns;
	}
	inline __attribute__((always_inline))
	constexpr const_iterator	cend() const
	{
		return const_iterator(__data) + rows * columns;
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
		return reverse_iterator(__data) + rows * columns;
	}
	inline __attribute__((always_inline))
	constexpr const_reverse_iterator	rend() const
	{
		return const_reverse_iterator(__data) + rows * columns;
	}
	inline __attribute__((always_inline))
	constexpr const_reverse_iterator	crend() const
	{
		return const_reverse_iterator(__data) + rows * columns;
	}

	inline __attribute__((always_inline))
	constexpr bool	empty() const noexcept
	{
		return (!bool(rows * columns));
	}
	inline __attribute__((always_inline))
	constexpr size_type	size() const noexcept
	{
		return rows * columns;
	}
	inline __attribute__((always_inline))
	constexpr size_type	elem_size() const noexcept
	{
		return sizeof(value_type);
	}
	inline __attribute__((always_inline))
	constexpr size_type	data_size() const noexcept
	{
		return sizeof(value_type) * columns * rows;
	}
	inline __attribute__((always_inline))
	void	fill(const_reference value)
	{
		for (auto& i : *this)
			i = value;
	}
};

__end_ns_td
