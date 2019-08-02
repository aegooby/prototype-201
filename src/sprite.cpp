
#include	"__common.hpp"
#include	"sprite.hpp"
#include	"filesystem.hpp"
#include	"component.hpp"

__begin_ns_td

const std::unordered_map<state, std::string>	sprite::names =
{
	{ state::idle, "idle" },
	{ state::left, "left" },
	{ state::right, "right" },
	{ state::up_right, "up_right" },
	{ state::attack, "attack" },
};
const std::unordered_map<std::string, state>	sprite::states =
{
	{ "idle", state::idle },
	{ "left", state::left },
	{ "right", state::right },
	{ "up_right", state::up_right },
	{ "attack", state::attack },
};

__end_ns_td
