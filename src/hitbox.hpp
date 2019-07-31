
#pragma	once
#include	"__common.hpp"

__begin_ns_td

struct	capsule
{
	float	x = 0; // the leftmost x value
	float	y = 0; // the bottom most y value of the rect
	float	height = 0;
	float	width = 0;
	
	inline __attribute__((always_inline))
	float	radius() const
	{
		return width / 2.0f;
	}
	inline __attribute__((always_inline))
	float 	right() const
	{
		return x + width;
	}
	inline __attribute__((always_inline))
	float 	top() const
	{
		return y + height;
	}
	inline __attribute__((always_inline))
	float 	left() const
	{
		return x;
	}
	inline __attribute__((always_inline))
	float 	bottom() const
	{
		return y;
	}
};

__end_ns_td
