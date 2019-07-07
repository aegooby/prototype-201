
#include	"__common.hpp"
#include	"component.hpp"
#include	"renderer.hpp"
#include	"filesystem.hpp"
#include	"sprite.hpp"
#include	"input.hpp"
#include	"event.hpp"
#include	"entity.hpp"

__begin_ns_td

component::~component() = default;

void	input_component::add_mapping(action action, keycode code, modifier modifier = modifier::NONE)
{
	for (auto& mapping : key_mappings)
	{
		if (mapping.second.first == code && mapping.second.second == modifier)
		{
			key_mappings.erase(mapping.first);
			break;
		}
	}
	if (mouse_mappings.count(action))
		mouse_mappings.erase(action);
	if (key_mappings.count(action))
		key_mappings.erase(action);
	key_mappings.emplace(action, std::make_pair(code, modifier));
}
void	input_component::add_mapping(action action, mousecode code, modifier modifier = modifier::NONE)
{
	for (auto& mapping : mouse_mappings)
	{
		if (mapping.second.first == code && mapping.second.second == modifier)
		{
			mouse_mappings.erase(mapping.first);
			break;
		}
	}
	if (key_mappings.count(action))
		key_mappings.erase(action);
	if (mouse_mappings.count(action))
		mouse_mappings.erase(action);
	mouse_mappings.emplace(action, std::make_pair(code, modifier));
}

void	input_component::remove_mapping(action action)
{
	key_mappings.erase(action);
	mouse_mappings.erase(action);
}

__end_ns_td
