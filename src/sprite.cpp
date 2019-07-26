
#include	"__common.hpp"
#include	"sprite.hpp"
#include	"filesystem.hpp"
#include	"component.hpp"

__begin_ns_td

const std::unordered_map<std::string, state>	sprite::states =
{
	{ "idle", state::idle },
	{ "left", state::left },
	{ "right", state::right },
	{ "attack", state::attack },
};

__end_ns_td
