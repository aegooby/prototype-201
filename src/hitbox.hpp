
#pragma	once
#include	"__common.hpp"

__begin_ns_td

struct	capsule
{
	float	x = 0; // the lefternmost x value
	float	y = 0; // the bottom most y value of the rect
	float	height = 0;
	float	width = 0;
	inline __attribute__((always_inline))
	float	radius() const
	{
		return width / 2;
	}
};

__end_ns_td
