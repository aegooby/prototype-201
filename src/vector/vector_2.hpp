
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
class	vector<value_type, 2> : public __vector_private::__vector_base<value_type, 2>
{
private:
	using __base = __vector_private::__vector_base<value_type, 2>;
public:
	using self_reference = vector<value_type, 2>&;
	using const_self_reference = const vector<value_type, 2>&;
	vector() = default;
	vector(value_type x, value_type y)
	: __base::__vector_base(x, y) {  }
	vector(const std::initializer_list<value_type>& list)
	: __base::__vector_base(list) {  }
	inline __attribute__((always_inline))
	self_reference	operator =(const std::initializer_list<value_type>& list)
	{
		if (list.size() > 2)
			throw std::overflow_error("td::vector: Initializer list is larger than vector size");
		for (typename __base::size_type i = 0; i < 2; ++i)
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
};

//	2D vector rotation uses a 2x2 rotational matrix multiplied by the vector (expanded here)

template	<typename value_type>
vector<value_type, 2>
rotation(const vector<value_type, 2>& vec, value_type angle)
{
	value_type	cast_angle = static_cast<value_type>(angle);
	vector<value_type, 2>	result;
	value_type	cos_angle = cos(cast_angle);
	value_type	sin_angle = sin(cast_angle);
	result[0] = vec[0] * cos_angle - vec[1] * sin_angle;
	result[1] = vec[1] * cos_angle + vec[0] * sin_angle;
	return result;
}


__end_ns_td
