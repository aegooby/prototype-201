
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

void	render_component::add_flipbook(const class state& state, float fps, const sprite_info& info)
{
	flipbooks.emplace(state, sprite_flipbook(__base::entity.type, state, fps, info));
}
void	render_component::remove_flipbook(const class state& state)
{
	flipbooks.erase(state);
}

__end_ns_td
