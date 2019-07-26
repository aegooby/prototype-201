
#include	"__common.hpp"
#include	"component.hpp"
#include	"render_system.hpp"
#include	"filesystem.hpp"
#include	"sprite.hpp"
#include	"input.hpp"
#include	"event.hpp"
#include	"entity.hpp"

__begin_ns_td

component::~component() = default;

void	input_component::add_mapping(state state, keycode code, modifier modifier = modifier::NONE)
{
	for (auto& mapping : key_mappings)
	{
		if (mapping.second.first == code && mapping.second.second == modifier)
		{
			key_mappings.erase(mapping.first);
			break;
		}
	}
	if (mouse_mappings.count(state))
		mouse_mappings.erase(state);
	if (key_mappings.count(state))
		key_mappings.erase(state);
	key_mappings.emplace(state, std::make_pair(code, modifier));
}
void	input_component::add_mapping(state state, mousecode code, modifier modifier = modifier::NONE)
{
	for (auto& mapping : mouse_mappings)
	{
		if (mapping.second.first == code && mapping.second.second == modifier)
		{
			mouse_mappings.erase(mapping.first);
			break;
		}
	}
	if (key_mappings.count(state))
		key_mappings.erase(state);
	if (mouse_mappings.count(state))
		mouse_mappings.erase(state);
	mouse_mappings.emplace(state, std::make_pair(code, modifier));
}

void	input_component::remove_mapping(state state)
{
	key_mappings.erase(state);
	mouse_mappings.erase(state);
}

__end_ns_td
