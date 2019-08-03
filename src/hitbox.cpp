
#include	"__common.hpp"
#include	"hitbox.hpp"

__begin_ns_td

bool	circle::check_collision(const circle& hitbox_a, const circle& hitbox_b)
{
	return distance(hitbox_a.center, hitbox_b.center) < hitbox_a.radius + hitbox_b.radius;
}

__end_ns_td
