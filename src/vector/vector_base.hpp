
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

class	__vector_private
{
private:
	template	<typename value_type, size_t dim>
	class	__vector_base;
public:
	template	<typename value_type, size_t dim>
	friend class	vector;
	
	//	Preventing instantiation, copying, and moving
	__vector_private() = delete;
	__vector_private(const __vector_private&) = delete;
	__vector_private(__vector_private&&) = delete;
	__vector_private&	operator =(const __vector_private&) = delete;
	__vector_private&	operator =(__vector_private&&) = delete;
};

template	<typename vtype, size_t dim>
class	__vector_private::__vector_base
{
	static_assert(std::is_literal_type_v<vtype>);
	static_assert(std::is_arithmetic_v<vtype>);
	static_assert(std::is_floating_point_v<vtype>);
	static_assert(std::is_signed_v<vtype>);
	static_assert(dim > 1);
public:
	using value_type = vtype;
	using reference = value_type&;
	using const_reference = const value_type&;
	using array_type = array<value_type, dim>;
	using array_reference = array<value_type, dim>&;
	using const_array_reference = const array<value_type, dim>&;
	using self_type = __vector_base<value_type, dim>;
	using const_self_type = const __vector_base<value_type, dim>;
	using self_reference = __vector_base<value_type, dim>&;
	using const_self_reference = const __vector_base<value_type, dim>&;
	using size_type = size_t;
	friend class	vector<value_type, dim>;
protected:
	array<value_type, dim>	__data;
public:
	constexpr __vector_base() = default;
	template	<typename ... types>
	constexpr __vector_base(types ... args)
	{
		static_assert(sizeof...(args) == dim);
		__data = { static_cast<value_type>(args)... };
	}
	__vector_base(const std::initializer_list<value_type>& list)
	{
		if (list.size() > dim)
			throw std::overflow_error("td::vector: Initializer list is larger than vector size");
		__data = list;
	}
	inline __attribute__((always_inline))
	self_reference operator =(const std::initializer_list<value_type>& list)
	{
		if (list.size() > dim)
			throw std::overflow_error("td::vector: Initializer list is larger than vector size");
		__data = list;
		return *this;
	}
	inline __attribute__((always_inline))
	constexpr reference		at(size_type index)
	{
		if (index >= dim)
			throw std::out_of_range("td::vector::at: Element is out of range");
		return __data[index];
	}
	inline __attribute__((always_inline))
	constexpr const_reference	at(size_type index) const
	{
		if (index >= dim)
			throw std::out_of_range("td::vector::at: Element is out of range");
		return __data[index];
	}
	inline __attribute__((always_inline))
	constexpr reference		operator [](size_type index)
	{
		if (index >= dim)
			throw std::out_of_range("td::vector::at: Element is out of range");
		return __data[index];
	}
	inline __attribute__((always_inline))
	constexpr const_reference	operator [](size_type index) const
	{
		if (index >= dim)
			throw std::out_of_range("td::vector::at: Element is out of range");
		return __data[index];
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
	value_type	length() const
	{
		value_type	sum = 0;
		for (const auto& i : __data)
		{
			sum += (i * i);
		}
		
		return sqrt(sum);;
	}
	inline __attribute__((always_inline))
	self_type	normalized() const
	{
		if (!*this) throw divide_by_zero("Cannot normalize zero vector");
		return	(*this / length());
	}
	inline __attribute__((always_inline))
	void	normalize()
	{
		*this /= length();
	}
	inline __attribute__((always_inline))
	void	project(const_self_reference normal)
	{
		if (!*this) throw divide_by_zero("Cannot project zero vector");
		*this = projection(*this, normal);
	}
	inline __attribute__((always_inline))
	self_type	projected(const_self_reference normal) const
	{
		if (!*this) throw divide_by_zero("Cannot project zero vector");
		return projection(*this, normal);
	}
	inline __attribute__((always_inline))
	void	reflect(const_self_reference normal)
	{
		if (!*this) throw divide_by_zero("Cannot reflect zero vector");
		*this = reflection(*this, normal);
	}
	inline __attribute__((always_inline))
	self_type	reflected(const_self_reference normal) const
	{
		if (!*this) throw divide_by_zero("Cannot reflect zero vector");
		return reflection(*this, normal);
	}
	
	inline __attribute__((always_inline))
	self_reference	operator +=(const_self_reference other)
	{
		for (size_type i = 0; i < dim; ++i)
		{
			__data[i] += other.__data[i];
		}
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator -=(const_self_reference other)
	{
		for (size_type i = 0; i < dim; ++i)
		{
			__data[i] -= other.__data[i];
		}
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator *=(value_type scalar)
	{
		for (auto& i : __data)
		{
			i *= scalar;
		}
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator /=(value_type scalar)
	{
		if (!bool(scalar)) throw divide_by_zero("Cannot divide by 0");
		for (auto& i : __data)
		{
			i /= scalar;
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
		self_type	zero_vector;
		zero_vector.__data.fill(0);
		return zero_vector;
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

template	<typename value_type, size_t dim>
inline __attribute__((always_inline)) bool	operator !(const vector<value_type, dim>& vector)
{
	return !(bool(vector));
}
template	<typename value_type, size_t dim>
inline __attribute__((always_inline)) vector<value_type, dim>
operator +(const vector<value_type, dim>& one, const vector<value_type, dim>& two)
{
	vector<value_type, dim>	result = one;
	result += two;
	return result;
}
template	<typename value_type, size_t dim>
inline __attribute__((always_inline)) vector<value_type, dim>
operator -(const vector<value_type, dim>& one, const vector<value_type, dim>& two)
{
	vector<value_type, dim>	result = one;
	result -= two;
	return result;
}


template	<typename value_type, size_t dim>
inline __attribute__((always_inline)) vector<value_type, dim>
operator *(const vector<value_type, dim>& vec, value_type scalar)
{
	vector<value_type, dim>	result = vec;
	result *= scalar;
	return result;
}
template	<typename value_type, size_t dim>
inline __attribute__((always_inline)) vector<value_type, dim>
operator *(value_type scalar, const vector<value_type, dim>& vec)
{
	vector<value_type, dim>	result = vec;
	result *= scalar;
	return result;
}

template	<typename value_type, size_t dim>
inline __attribute__((always_inline)) vector<value_type, dim>
operator /(const vector<value_type, dim>& vec, value_type scalar)
{
	vector<value_type, dim>	result = vec;
	result /= scalar;
	return result;
}

template	<typename value_type, size_t dim>
inline __attribute__((always_inline))
bool	operator ==(const vector<value_type, dim>& one, const vector<value_type, dim>& two)
{
	for (size_t i = 0; i < dim; ++i)
	{
		if (one[i] != two[i])
		{
			return false;
		}
	}
	return true;
}
template	<typename value_type, size_t dim>
inline __attribute__((always_inline)) bool	operator !=(const vector<value_type, dim>& one, const vector<value_type, dim>& two)
{
	return !(one == two);
}
template	<typename value_type, size_t dim>
std::ostream&
operator <<(std::ostream& ostream, const vector<value_type, dim>& vec)
{
	std::string	str;
	str += "<";
	for (const auto& i : vec.array())
	{
		str += std::to_string(i) + ", ";
	}
	str = str.substr(0, str.length() - 2);
	str += ">";
	return ostream << str;
}
template	<typename value_type, size_t dim>
value_type
dot(const vector<value_type, dim>& one, const vector<value_type, dim>& two)
{
	value_type	result = 0;
	for (size_t i = 0; i < dim; ++i)
	{
		result += (one[i] * two[i]);
	}
	return result;
}
template	<typename value_type, size_t dim>
value_type	distance(const vector<value_type, dim>& one, const vector<value_type, dim>& two)
{
	vector<value_type, dim>	result;
	result = one - two;
	return result.length();
}
template	<typename value_type, size_t dim>
value_type angle(const vector<value_type, dim>& one, const vector<value_type, dim>& two)
{
	if (!one || !two) throw divide_by_zero("Cannot find angle for zero vector(s)");
	return acos(dot(one, two) / (one.length() * two.length()));
}

template	<typename value_type, size_t dim>
inline __attribute__((always_inline)) vector<value_type, dim>
projection(const vector<value_type, dim>& vec, const vector<value_type, dim>& normal)
{
	if (!vec)
		throw divide_by_zero("Cannot project zero vector");
	if (!normal)
		throw divide_by_zero("Cannot project over zero normal");
	return (dot(vec, normal.normalized()) * normal.normalized());
}

template	<typename value_type, size_t dim>
vector<value_type, dim>
reflection(const vector<value_type, dim>& vec, const vector<value_type, dim>& normal)
{
	if (!vec)
		throw divide_by_zero("Cannot reflect zero vector");
	if (!normal)
		throw divide_by_zero("Cannot reflect over zero normal");
	return (vec - (projection(vec, normal) * value_type(2)));
}

template	<typename value_type, size_t dim>
vector<value_type, dim>	lerp(const vector<value_type, dim>& vector_start,
							 const vector<value_type, dim>& vector_end,
							 value_type factor)
{
	return ((vector_end - vector_start) * factor) + vector_start;
}

__end_ns_td
