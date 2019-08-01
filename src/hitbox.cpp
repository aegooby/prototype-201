
#include	"__common.hpp"
#include	"hitbox.hpp"

__begin_ns_td

bool	circle::check_collision(const circle& hitbox_a, const circle& hitbox_b)
{
	return distance(hitbox_a.center, hitbox_b.center) < hitbox_a.radius + hitbox_b.radius;
}

bool	capsule::check_collision(const capsule& hitbox_a, const capsule& hitbox_b)
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
