
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
	for (auto& mapping : __mappings)
	{
		switch (mapping.second.first)
		{
			case source::mouse:
				if (mouse.button_scan(mousecode(mapping.second.second)))
					;
				break;
			case source::keyboard:
				if (keyboard.key_scan(keycode(mapping.second.second)))
					;
				break;
			default:
				break;
		}
	}
}

void	input_component::map(keycode code, action action)
{
	__mappings.emplace(action, std::make_pair(source::keyboard, int16_t(code)));
}
void	input_component::map(mousecode code, action action)
{
	__mappings.emplace(action, std::make_pair(source::mouse, int16_t(code)));
}

__end_ns_td
