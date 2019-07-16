
#include	"__common.hpp"
#include	"physics_system.hpp"
#include	"entity_manager.hpp"

__begin_ns_td

void	physics_system::update()
{
	for (auto& entity : __registered_entities)
	{
		auto&	transform = entity.second.get().component<transform_component>();
		transform.velocity += transform.acceleration;
		transform.position += transform.velocity;
	}
}

__end_ns_td
