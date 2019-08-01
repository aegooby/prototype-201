
#pragma	once
#include	"../__common.hpp"
#include	"../math_base.hpp"
#include	"../array.hpp"
#include	"point_base.hpp"
#include	<initializer_list>
#include	<exception>
#include	<stdexcept>

__begin_ns_td

template	<typename value_type>
class	point<value_type, 2>
{
	static_assert(std::is_literal_type_v<value_type>);
	static_assert(std::is_arithmetic_v<value_type>);
	static_assert(std::is_integral_v<value_type>);
	static_assert(std::is_signed_v<value_type>);
public:
	value_type	x = value_type(), y = value_type();
public:
	using self_reference = point<value_type, 2>&;
	using const_self_reference = const point<value_type, 2>&;
	using self_type = point<value_type, 2>;
	using size_type = size_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	point() = default;
	point(value_type x, value_type y) : x(x), y(y) {  }
	point(const std::initializer_list<value_type>& list)
	{
		if (list.size() > 2)
			throw std::overflow_error("td::point: Initializer list is larger than point size");
		x = *(list.begin());
		y = *(list.begin() + 1);
	}
	inline __attribute__((always_inline))
	self_reference	operator =(const std::initializer_list<value_type>& list)
	{
		if (list.size() > 2)
			throw std::overflow_error("td::point: Initializer list is larger than point size");
		x = *(list.begin());
		y = *(list.begin() + 1);
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator =(const_self_reference other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	inline __attribute__((always_inline))
	constexpr reference		at(size_type index)
	{
		switch (index)
		{
			case 0:
				return x;
				break;
			case 1:
				return y;
				break;
			default:
				throw std::out_of_range("td::point::at: Element is out of range");
				break;
		}
	}
	inline __attribute__((always_inline))
	constexpr const_reference	at(size_type index) const
	{
		switch (index)
		{
			case 0:
				return x;
				break;
			case 1:
				return y;
				break;
			default:
				throw std::out_of_range("td::point::at: Element is out of range");
				break;
		}
	}
	inline __attribute__((always_inline))
	constexpr reference		operator [](size_type index)
	{
		switch (index)
		{
			case 0:
				return x;
				break;
			case 1:
				return y;
				break;
			default:
				throw std::out_of_range("td::point::at: Element is out of range");
				break;
		}
	}
	inline __attribute__((always_inline))
	constexpr const_reference	operator [](size_type index) const
	{
		switch (index)
		{
			case 0:
				return x;
				break;
			case 1:
				return y;
				break;
			default:
				throw std::out_of_range("td::point::at: Element is out of range");
				break;
		}
	}
	inline __attribute__((always_inline))
	self_reference	operator +=(const_self_reference other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator -=(const_self_reference other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator -()
	{
		*this *= -1;
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator +()
	{
		return *this;
	}
	inline __attribute__((always_inline))
	constexpr static self_type	zero()
	{
		return point();
	}
	inline __attribute__((always_inline))
	explicit operator bool() const
	{
		return (*this != this->zero());
	}
	inline __attribute__((always_inline))
	bool	operator !() const
	{
		return !(bool(this));
	}
};

template	<typename value_type>
inline __attribute__((always_inline))
bool	operator ==(const point<value_type, 2>& one, const point<value_type, 2>& two)
{
	
	return (one.x == two.x && one.y == two.y);
}

__end_ns_td
