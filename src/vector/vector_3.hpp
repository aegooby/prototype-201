
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
class	vector<value_type, 3> : public __vector_private::__vector_base<value_type, 3>
{
private:
	using __base = __vector_private::__vector_base<value_type, 3>;
public:
	using self_reference = vector<value_type, 3>&;
	using const_self_reference = const vector<value_type, 3>&;
	vector() = default;
	vector(value_type x, value_type y, value_type z)
	: __base::__vector_base(x, y, z) {  }
	vector(const std::initializer_list<value_type>& list)
	: __base::__vector_base(list) {  }
	inline __attribute__((always_inline))
	self_reference	operator =(const std::initializer_list<value_type>& list)
	{
		if (list.size() > 3)
			throw std::overflow_error("td::vector: Initializer list is larger than vector size");
		for (typename __base::size_type i = 0; i < 3; ++i)
		{
			reinterpret_cast<value_type*>(__base::__data.data())[i] = *(list.begin() + i);
		}
		return *this;
	}
	inline __attribute__((always_inline))
	self_reference	operator =(const_self_reference other)
	{
		__base::__data = other.__data;
		return *this;
	}
	value_type&	x = __base::at(0);
	value_type&	y = __base::at(1);
	value_type&	z = __base::at(2);
};

template	<typename value_type>
vector<value_type, 3>	cross(const vector<value_type, 3>& one,
							  const vector<value_type, 3>& two)
{
	vector<value_type, 3>	result;
	result[0] = (one[1] * two[2]) - (one[2] * two[1]);
	result[1] = (one[2] * two[0]) - (one[0] * two[2]);
	result[2] = (one[0] * two[1]) - (one[1] * two[0]);
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

__end_ns_td
