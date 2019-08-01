
#pragma	once
#include	"../__common.hpp"
#include	"../math_base.hpp"
#include	"../array.hpp"
#include	"vector_base.hpp"
#include	<initializer_list>
#include	<exception>
#include	<stdexcept>

__begin_ns_td

template	<typename value_type>
class	vector<value_type, 3>
{
	static_assert(std::is_literal_type_v<value_type>);
	static_assert(std::is_arithmetic_v<value_type>);
	static_assert(std::is_floating_point_v<value_type>);
	static_assert(std::is_signed_v<value_type>);
public:
	value_type	x = value_type(), y = value_type(), z = value_type();
public:
	using self_reference = vector<value_type, 3>&;
	using const_self_reference = const vector<value_type, 3>&;
	using self_type = vector<value_type, 3>;
	using size_type = size_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	vector() = default;
	vector(value_type x, value_type y, value_type z) : x(x), y(y), z(z) {  }
	vector(const std::initializer_list<value_type>& list)
	{
		if (list.size() > 3)
			throw std::overflow_error("td::vector: Initializer list is larger than vector size");
		x = *(list.begin());
		y = *(list.begin() + 1);
		z = *(list.begin() + 2);
	}
	inline __attribute__((always_inline))
	self_reference	operator =(const std::initializer_list<value_type>& list)
	{
		if (list.size() > 3)
			throw std::overflow_error("td::vector: Initializer list is larger than vector size");
		x = *(list.begin());
		y = *(list.begin() + 1);
		z = *(list.begin() + 2);
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator =(const_self_reference other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
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
			case 2:
				return z;
				break;
			default:
				throw std::out_of_range("td::vector::at: Element is out of range");
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
			case 2:
				return z;
				break;
			default:
				throw std::out_of_range("td::vector::at: Element is out of range");
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
			case 2:
				return z;
				break;
			default:
				throw std::out_of_range("td::vector::at: Element is out of range");
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
			case 2:
				return z;
				break;
			default:
				throw std::out_of_range("td::vector::at: Element is out of range");
				break;
		}
	}
	inline __attribute__((always_inline))
	value_type	norm() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}
	inline __attribute__((always_inline))
	self_type	normalized() const
	{
		if (!*this) throw divide_by_zero("Cannot normalize zero vector");
		return	(*this / norm());
	}
	inline __attribute__((always_inline))
	void	normalize()
	{
		*this /= norm();
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
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator -=(const_self_reference other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator *=(value_type scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator /=(value_type scalar)
	{
		if (!bool(scalar)) throw divide_by_zero("Cannot divide by 0");
		x /= scalar;
		y /= scalar;
		z /= scalar;
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
		return vector();
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
vector<value_type, 3>	cross(const vector<value_type, 3>& one,
							  const vector<value_type, 3>& two)
{
	vector<value_type, 3>	result;
	result.at(0) = (one.at(1) * two.at(2)) - (one.at(2) * two.at(1));
	result.at(1) = (one.at(2) * two.at(0)) - (one.at(0) * two.at(2));
	result.at(2) = (one.at(0) * two.at(1)) - (one.at(1) * two.at(0));
	return result;
}
template	<typename value_type>
vector<value_type, 3>	rotation(const vector<value_type, 3>& vec,
								 const vector<value_type, 3>& axis,
								 value_type angle)
{
	//	3D vector axis-angle rotation uses Rodrigues's formula
	return (vec * cos(angle) + cross(vec, axis.normalized()) * sin(angle) + projection(vec, axis) * (1 - cos(angle)));
}

template	<typename value_type>
inline __attribute__((always_inline))
bool	operator ==(const vector<value_type, 3>& one, const vector<value_type, 3>& two)
{
	
	return (one.x == two.x && one.y == two.y && one.z == two.z);
}

__end_ns_td
