
#include	"__common.hpp"
#include	"component.hpp"
#include	"renderer.hpp"
#include	"filesystem.hpp"
#include	"sprite.hpp"

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

__end_ns_td
