
#pragma	once
#include	"__common.hpp"
#include	"vector.hpp"

__begin_ns_td

struct	hitbox {  };

struct	circle : public hitbox
{
protected:
	vector_2	__center = vector_2();
	float		__radius = 0.0f;
public:
	circle() = default;
	circle(vector_2 center, float radius) : __center(center), __radius(radius) {  }
	circle(float x, float y, float radius) : __center(x, y), __radius(radius) {  }
	~circle() = default;
	
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
};

// DEPRECATED
inline bool	check_collision(capsule& hitbox_a, capsule& hitbox_b)
{
	float	left_a = hitbox_a.left(), left_b = hitbox_b.left();
	float	right_a = hitbox_a.right(), right_b = hitbox_b.right();
	float	xcenter_a = hitbox_a.left() + hitbox_a.radius();
	float	xcenter_b = hitbox_b.left() + hitbox_b.radius();
	float	ytopcenter_a = hitbox_a.bottom() + hitbox_a.height();
	float	ytopcenter_b = hitbox_b.bottom() + hitbox_b.height();
	float	ybotcenter_a = hitbox_a.bottom();
	float	ybotcenter_b = hitbox_b.bottom();
	
	float	xdist = std::abs(xcenter_b - xcenter_a);
	
	// If capsule B is above capsule A
	auto	distsquared1 = [xdist, ytopcenter_a, ybotcenter_b]()
	{
		float	ydist = ybotcenter_b - ytopcenter_a;
		return (xdist * xdist) + (ydist * ydist);
	};
	
	// If capsule A is above capsule B
	auto	distsquared2 = [xdist, ybotcenter_a, ytopcenter_b]()
	{
		float	ydist = ybotcenter_a - ytopcenter_b;
		return (xdist * xdist) + (ydist * ydist);
	};
	
	if (right_a >= left_b)
	{
		return true;
	}
	if (right_b <= left_a)
	{
		return true;
	}
	if (distsquared1() <= (hitbox_a.radius() + hitbox_b.radius()) * (hitbox_a.radius() + hitbox_b.radius()))
	{
		return true;
	}
	if (distsquared2() <= (hitbox_b.radius() + hitbox_a.radius()) * (hitbox_b.radius() + hitbox_a.radius()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

__end_ns_td
