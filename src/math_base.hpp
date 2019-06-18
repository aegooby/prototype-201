
#pragma	once
#include	"__common.hpp"
#include	<type_traits>
#include	<cmath>

__begin_ns_td

template	<typename value_type>
static constexpr
std::enable_if_t<std::is_floating_point_v<value_type>, value_type>
pi = static_cast<value_type>(M_PI);

template	<typename value_type>
inline __attribute__((always_inline))
constexpr std::enable_if_t<std::is_arithmetic_v<value_type>, value_type>
sign(value_type value)
{
	return value_type(value >= 0 ? 1 : -1);
}
template	<typename value_type>
inline __attribute__((always_inline))
std::enable_if_t<std::is_floating_point_v<value_type>, value_type>
simplify_angle(value_type theta)
{
	return std::atan2(std::sin(theta), std::cos(theta));
}
template	<typename value_type>
inline __attribute__((always_inline))
constexpr
std::enable_if_t<std::is_floating_point<value_type>::value, value_type>
unit_circle(value_type theta)
{
	return value_type(simple_angle(theta) > 0 ? simple_angle(theta) : simple_angle(theta) + 2 * pi<value_type>);
}

template	<typename value_type, typename	function_type>
std::enable_if_t<std::is_arithmetic_v<value_type>, value_type>
sigma(uint64_t start, uint64_t end, function_type function)
{
	value_type result = 0;
	for (uint64_t i = start; i < end; ++i)
	{
		result += function(i);
	}
	return result;
}
template	<typename value_type>
inline __attribute__((always_inline))
constexpr std::enable_if_t<std::is_floating_point_v<value_type>, value_type>
radians(value_type degrees) noexcept
{
	return static_cast<value_type>(180) * degrees / pi<value_type>;
}
template	<typename value_type>
inline __attribute__((always_inline))
constexpr std::enable_if_t<std::is_floating_point_v<value_type>, value_type>
degrees(value_type radians) noexcept
{
	return  radians * pi<value_type> / static_cast<value_type>(180);
}

template	<typename value_type>
inline __attribute__((always_inline))
constexpr std::enable_if_t<std::is_floating_point_v<value_type>, bool>
equal(value_type __a, value_type __b, value_type threshold) noexcept
{
	return (std::abs(__a - __b) <= threshold);
}

class	divide_by_zero : public std::domain_error
{
public:
	explicit divide_by_zero(const std::string& what) noexcept : std::domain_error(what) {  }
	explicit divide_by_zero(const char* what) noexcept : std::domain_error(what) {  }
	virtual ~divide_by_zero() = default;
};

__end_ns_td
