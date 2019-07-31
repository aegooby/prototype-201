
#pragma	once
#include	"__common.hpp"

__begin_ns_td

struct	capsule
{
	float	x = 0; // the lefternmost x value
	float	y = 0; // the bottom most y value of the rect
	float	height = 0;
	float	width = 0;
	inline __attribute__((always_inline));

	float getx() const 
	{
		return x;
	}
	float gety() const 
	{
		return y;
	}
	float getwidth() const 
	{
		return width;
	}
	float getheight() const
	{
		return height;
	}
	float	radius() const
	{
		return width / 2;
	}
	float getright() const
	{
		return x + width;
	}
	float gettop() const
	{
		return y + height;
	}
};

__end_ns_td
