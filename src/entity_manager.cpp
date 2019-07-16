
#include	"__common.hpp"
#include	"entity_manager.hpp"
#include	"entity.hpp"

__begin_ns_td

void	entity_manager::add_entity(const std::string& name)
{
	entities.emplace(__entityc, std::make_unique<entity>(__entityc, name, world));
	++__entityc;
}
void	entity_manager::remove_entity(id_t id)
{
	entities.erase(id);
}

__end_ns_td
