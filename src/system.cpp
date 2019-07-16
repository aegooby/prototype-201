
#include	"__common.hpp"
#include	"system.hpp"
#include	"world.hpp"
#include	"entity.hpp"

__begin_ns_td

std::unordered_map<std::type_index, enum system::flag>	system::flags =
{
	{ typeid(render_component), system::flag::render },
	{ typeid(transform_component), system::flag::transform },
	{ typeid(collision_component), system::flag::collision },
	{ typeid(input_component), system::flag::input },
	{ typeid(audio_component), system::flag::audio },
};

system::system(class world& world) : world(world) {  }
void	system::register_entity(class entity& entity)
{
	if (!__registered_entities.count(entity.id()))
		__registered_entities.emplace(entity.id(), entity);
}
void	system::deregister_entity(class entity& entity)
{
	__registered_entities.erase(entity.id());
}

__end_ns_td
