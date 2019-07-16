
#include	"__common.hpp"
#include	"newton.hpp"
#include	"entity_manager.hpp"

__begin_ns_td

void	update(entity_manager& entity_manager)
{
	for (auto& entity : entity_manager.entities)
	{
		//			for (auto& component : entity.second->components)
		//			{
		//				if (auto transform = memory::weak_cast<transform_component*>(component))
		//				{
		//					entity.second->position += transform->velocity;
		//					transform->velocity += transform->acceleration;
		//				}
		//			}
	}
}

__end_ns_td
