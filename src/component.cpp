
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

void	render_component::render(td::renderer& renderer)
{
	// TODO: THIS IS TEMPORARY
	for (auto& child : __children)
	{
		child.second->render(renderer, *this);
	}
}

void	render_component::add_child(std::unique_ptr<sprite_base>&& child)
{
	using ptr = std::unique_ptr<sprite_base>;
	__children.emplace(child->name(), std::forward<ptr>(child));
}

void	render_component::remove_child(const std::string& name)
{
	__children.erase(name);
}

void	input_component::map(action action, keycode code, modifier modifier = modifier::NONE)
{
	for (auto& mapping : __key_mappings)
	{
		if (mapping.second.first == code && mapping.second.second == modifier)
		{
			__key_mappings.erase(mapping.first);
			break;
		}
	}
	if (__mouse_mappings.count(action))
		__mouse_mappings.erase(action);
	if (__key_mappings.count(action))
		__key_mappings.erase(action);
	__key_mappings.emplace(action, std::make_pair(code, modifier));
}
void	input_component::map(action action, mousecode code, modifier modifier = modifier::NONE)
{
	for (auto& mapping : __mouse_mappings)
	{
		if (mapping.second.first == code && mapping.second.second == modifier)
		{
			__mouse_mappings.erase(mapping.first);
			break;
		}
	}
	if (__key_mappings.count(action))
		__key_mappings.erase(action);
	if (__mouse_mappings.count(action))
		__mouse_mappings.erase(action);
	__mouse_mappings.emplace(action, std::make_pair(code, modifier));
}
void	input_component::read(const td::keyboard& keyboard, const td::mouse& mouse)
{
	for (auto& mapping : __key_mappings)
	{
		if (keyboard.down(mapping.second.first) && keyboard.modifier(mapping.second.second))
		{
			entity.event_handler.add_event(std::make_unique<td::action_event>(mapping.first));
		}
	}
	for (auto& mapping : __mouse_mappings)
	{
		if (mouse.down(mapping.second.first) && keyboard.modifier(mapping.second.second))
		{
			entity.event_handler.add_event(std::make_unique<td::action_event>(mapping.first));
		}
	}
}

__end_ns_td
