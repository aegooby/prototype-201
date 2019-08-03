
#pragma	once
#include	"__common.hpp"

__begin_ns_td

enum class	direction_state
{
	left,
	right,
	up,
	down,
	up_right,
	up_left,
	down_right,
	down_left,
};
enum class	movement_state
{
	idle,
	walk,
	run,
	dash,
};
enum class	attack_state
{
	neutral,
	melee,
	ranged,
};
class	state
{
public:
	direction_state	direction;
	movement_state	movement;
	attack_state	attack;
	state() = default;
	state(direction_state direction, movement_state movement, attack_state attack) : direction(direction), movement(movement), attack(attack) {  }
};

bool	operator ==(const state& __a, const state& __b)
{
	return (__a.direction == __b.direction && __a.movement == __b.movement && __a.attack == __b.attack);
}

enum class	entity_type
{
	player,
};

__end_ns_td
