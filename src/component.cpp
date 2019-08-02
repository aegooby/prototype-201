
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

void	render_component::add_flipbook(const std::string& name, float fps, const sprite_info& info)
{
	flipbooks.emplace(name, sprite_flipbook(__base::entity.name(), name, fps, info));
}
void	render_component::remove_flipbook(const std::string& name)
{
	flipbooks.erase(name);
}

__end_ns_td
