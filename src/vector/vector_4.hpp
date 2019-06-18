
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
class	vector<value_type, 4> : public __vector_private::__vector_base<value_type, 4>
{
private:
	using __base = __vector_private::__vector_base<value_type, 4>;
public:
	using self_reference = vector<value_type, 4>&;
	vector() = default;
	vector(value_type x, value_type y, value_type z, value_type r)
	: __base::__vector_base(x, y, z, r) {  }
	vector(const std::initializer_list<value_type>& list)
	: __base::__vector_base(list) {  }
	inline __attribute__((always_inline))
	self_reference	operator =(const std::initializer_list<value_type>& list)
	{
		if (list.size() > 4)
			throw std::overflow_error("td::vector: Initializer list is larger than vector size");
		for (typename __base::size_type i = 0; i < 4; ++i)
		{
			reinterpret_cast<value_type*>(__base::__data.data())[i] = *(list.begin() + i);
		}
		return *this;
	}
	inline __attribute__((always_inline)) value_type	x() const	{ return __base::at(0); }
	inline __attribute__((always_inline)) value_type	y() const	{ return __base::at(1); }
	inline __attribute__((always_inline)) value_type	z() const	{ return __base::at(2); }
	inline __attribute__((always_inline)) value_type	r() const	{ return __base::at(3); }
	inline __attribute__((always_inline)) void	x(value_type x)	{ __base::at(0) = x; }
	inline __attribute__((always_inline)) void	y(value_type y)	{ __base::at(1) = y; }
	inline __attribute__((always_inline)) void	z(value_type z)	{ __base::at(2) = z; }
	inline __attribute__((always_inline)) void	r(value_type r)	{ __base::at(3) = r; }
};

__end_ns_td
