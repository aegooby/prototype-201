
#include	"__common.hpp"
#include	"component.hpp"
#include	"renderer.hpp"
#include	"filesystem.hpp"
#include	"sprite.hpp"
#include	"input.hpp"

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

void	input_component::read(const td::keyboard& keyboard, const td::mouse& mouse)
{
	for (auto& mapping : __key_mappings)
	{
		if (keyboard.key_down(mapping.second))
			;
		if (keyboard.key_scan(mapping.second))
			;
		if (keyboard.key_up(mapping.second))
			;
	}
	for (auto& mapping : __mouse_mappings)
	{
		if (mouse.button_down(mapping.second))
			;
		if (mouse.button_scan(mapping.second))
			;
		if (mouse.button_up(mapping.second))
			;
	}
}

void	input_component::map(action action, keycode code)
{
	for (auto& mapping : __key_mappings)
	{
		if (mapping.second == code)
		{
			__key_mappings.erase(mapping.first);
			break;
		}
	}
	if (__mouse_mappings.count(action))
		__mouse_mappings.erase(action);
	if (__key_mappings.count(action))
		__key_mappings.erase(action);
	__key_mappings.emplace(action, code);
}
void	input_component::map(action action, mousecode code)
{
	for (auto& mapping : __mouse_mappings)
	{
		if (mapping.second == code)
		{
			__mouse_mappings.erase(mapping.first);
			break;
		}
	}
	if (__key_mappings.count(action))
		__key_mappings.erase(action);
	if (__mouse_mappings.count(action))
		__mouse_mappings.erase(action);
	__mouse_mappings.emplace(action, code);
}

__end_ns_td
