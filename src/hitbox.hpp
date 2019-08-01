
#pragma	once
#include	"__common.hpp"
#include	"vector.hpp"

__begin_ns_td

struct	hitbox {  };

struct	circle : public hitbox
{
public:
	vector_2	center = vector_2();
	float		radius = 0.0f;
	float&		x = center.x;
	float&		y = center.y;
public:
	circle() = default;
	circle(vector_2 center, float radius) : center(center), radius(radius) {  }
	circle(float x, float y, float radius) : center(x, y), radius(radius) {  }
	~circle() = default;
	static bool	check_collision(const circle&, const circle&);
};

// DEPRECATED
struct	capsule : public hitbox
{
protected:
	float	__left = 0;
	float	__bottom = 0;
	float	__width = 0;
	float	__height = 0;
public:
	capsule() = default;
	capsule(float left, float bottom, float width, float height) : __left(left), __bottom(bottom), __width(width), __height(height) {  }
	inline __attribute__((always_inline))
	float	radius() const
	{
		return __width / 2.0f;
	}
	inline __attribute__((always_inline))
	float 	right() const
	{
		return __left + __width;
	}
	inline __attribute__((always_inline))
	float 	top() const
	{
		return __bottom + __height;
	}
	inline __attribute__((always_inline))
	float 	left() const
	{
		return __left;
	}
	inline __attribute__((always_inline))
	float 	bottom() const
	{
		return __bottom;
	}
	inline __attribute__((always_inline))
	float	width() const
	{
		return __width;
	}
	inline __attribute__((always_inline))
	float	height() const
	{
		return __height;
	}
	static bool	check_collision(const capsule&, const capsule&);
};


__end_ns_td
