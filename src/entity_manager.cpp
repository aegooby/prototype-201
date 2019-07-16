
#include	"__common.hpp"
#include	"entity_manager.hpp"
#include	"entity.hpp"
#include	"world.hpp"

__begin_ns_td

entity&	entity_manager::new_entity(const std::string& name, class world& world)
{
	entities.emplace(__entityc, std::make_unique<entity>(__entityc, name, world));
	auto	__entityc_temp = __entityc;
	++__entityc;
	return *entities.at(__entityc_temp);
}
void	entity_manager::delete_entity(id_t id)
{
	entities.erase(id);
}

__end_ns_td
