
#pragma	once
#include	"../__common.hpp"
#include	"../math_base.hpp"
#include	"../array.hpp"
#include	<initializer_list>
#include	<ostream>
#include	<sstream>
#include	<exception>
#include	<stdexcept>

__begin_ns_td

class	__point_private
{
private:
	template	<typename value_type, size_t dim>
	class	__point_base;
public:
	template	<typename value_type, size_t dim>
	friend class	point;
	
	//	Preventing instantiation, copying, and moving
	__point_private() = delete;
	__point_private(const __point_private&) = delete;
	__point_private(__point_private&&) = delete;
	__point_private&	operator =(const __point_private&) = delete;
	__point_private&	operator =(__point_private&&) = delete;
};

template	<typename __value_type, size_t dim>
class	__point_private::__point_base
{
	static_assert(std::is_literal_type_v<__value_type>);
	static_assert(std::is_arithmetic_v<__value_type>);
	static_assert(std::is_integral_v<__value_type>);
	static_assert(std::is_signed_v<__value_type>);
	static_assert(dim > 1);
public:
	using value_type = __value_type;
	using reference = value_type&;
	using const_reference = const value_type&;
	using array_type = array<value_type, dim>;
	using array_reference = array<value_type, dim>&;
	using const_array_reference = const array<value_type, dim>&;
	using self_type = __point_base<value_type, dim>;
	using const_self_type = const __point_base<value_type, dim>;
	using self_reference = __point_base<value_type, dim>&;
	using const_self_reference = const __point_base<value_type, dim>&;
	using size_type = size_t;
	friend class	point<value_type, dim>;
protected:
	array<value_type, dim>	__data;
public:
	constexpr __point_base() = default;
	template	<typename ... types>
	constexpr __point_base(types&& ... args)
	{
		static_assert(sizeof...(args) == dim);
		__data = { static_cast<value_type>(std::forward<types>(args))... };
	}
	__point_base(const std::initializer_list<value_type>& list)
	{
		if (list.size() > dim)
			throw std::overflow_error("td::point: Initializer list is larger than point size");
		__data = list;
	}
	inline __attribute__((always_inline))
	self_reference operator =(const std::initializer_list<value_type>& list)
	{
		if (list.size() > dim)
			throw std::overflow_error("td::point: Initializer list is larger than point size");
		__data = list;
		return *this;
	}
	inline __attribute__((always_inline))
	constexpr reference		at(size_type index)
	{
		if (index >= dim)
			throw std::out_of_range("td::point::at: Element is out of range");
		return __data.at(index);
	}
	inline __attribute__((always_inline))
	constexpr const_reference	at(size_type index) const
	{
		if (index >= dim)
			throw std::out_of_range("td::point::at: Element is out of range");
		return __data.at(index);
	}
	inline __attribute__((always_inline))
	constexpr reference		operator [](size_type index)
	{
		if (index >= dim)
			throw std::out_of_range("td::point::at: Element is out of range");
		return __data.at(index);
	}
	inline __attribute__((always_inline))
	constexpr const_reference	operator [](size_type index) const
	{
		if (index >= dim)
			throw std::out_of_range("td::point::at: Element is out of range");
		return __data.at(index);
	}
	inline __attribute__((always_inline))
	auto&	array()	{ return __data; }
	inline __attribute__((always_inline))
	const auto&	array() const { return __data; }
	inline __attribute__((always_inline))
	constexpr size_type	size() const noexcept	{ return dim; }
	
	inline __attribute__((always_inline))
	constexpr size_type	elem_size() const noexcept	{ return sizeof(value_type); }
	inline __attribute__((always_inline))
	constexpr size_type	data_size() const noexcept	{ return __data.data_size(); }
	
	inline __attribute__((always_inline))
	self_reference	operator +=(const_self_reference other)
	{
		for (size_type i = 0; i < dim; ++i)
		{
			__data.at(i) += other.__data.at(i);
		}
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator -=(const_self_reference other)
	{
		for (size_type i = 0; i < dim; ++i)
		{
			__data.at(i) -= other.__data.at(i);
		}
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
		self_type	zero_point;
		zero_point.__data.fill(0);
		return zero_point;
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

template	<typename __value_type, size_t dim>
class	point : public __point_private::__point_base<__value_type, dim>
{
public:
	using __base = __point_private::__point_base<__value_type, dim>;
	using value_type = typename __base::value_type;
	using reference = typename __base::reference;
	using const_reference = typename __base::const_reference;
	using array_type = typename __base::array_type;
	using array_reference = typename __base::array_reference;
	using const_array_reference = typename __base::const_array_reference;
	using self_type = point<value_type, dim>;
	using const_self_type = const point<value_type, dim>;
	using self_reference = point<value_type, dim>&;
	using const_self_reference = const point<value_type, dim>&;
	using size_type = typename __base::size_type;
public:
	constexpr point() = default;
	template	<typename ... types>
	constexpr point(types&& ... args) : __base(std::forward<types>(args)...) {  }
	point(const std::initializer_list<value_type>& list) : __base(list) {  }
	inline __attribute__((always_inline))
	self_reference operator =(const std::initializer_list<value_type>& list)
	{
		if (list.size() > dim)
			throw std::overflow_error("td::point: Initializer list is larger than point size");
		__base::__data = list;
		return *this;
	}
};

template	<typename value_type, size_t dim>
inline __attribute__((always_inline)) bool	operator !(const point<value_type, dim>& point)
{
	return !(bool(point));
}
template	<typename value_type, size_t dim>
inline __attribute__((always_inline)) point<value_type, dim>
operator +(const point<value_type, dim>& one, const point<value_type, dim>& two)
{
	point<value_type, dim>	result = one;
	result += two;
	return result;
}
template	<typename value_type, size_t dim>
inline __attribute__((always_inline)) point<value_type, dim>
operator -(const point<value_type, dim>& one, const point<value_type, dim>& two)
{
	point<value_type, dim>	result = one;
	result -= two;
	return result;
}

template	<typename value_type, size_t dim>
inline __attribute__((always_inline))
bool	operator ==(const point<value_type, dim>& one, const point<value_type, dim>& two)
{
	for (size_t i = 0; i < dim; ++i)
	{
		if (one.at(i) != two.at(i))
		{
			return false;
		}
	}
	return true;
}
template	<typename value_type, size_t dim>
inline __attribute__((always_inline)) bool	operator !=(const point<value_type, dim>& one, const point<value_type, dim>& two)
{
	return !(one == two);
}
template	<typename value_type, size_t dim>
std::ostream&
operator <<(std::ostream& ostream, const point<value_type, dim>& pt)
{
	std::string	str;
	str += "(";
	for (const auto& i : pt.array())
	{
		str += std::to_string(i) + ", ";
	}
	str = str.substr(0, str.length() - 2);
	str += ")";
	return ostream << str;
}

__end_ns_td
