
#include	"__common.hpp"
#include	"physics_system.hpp"
#include	"entity_manager.hpp"
#include	"event.hpp"
#include	"world.hpp"

__begin_ns_td

void	physics_system::start()
{
	world.event_bus.subscribe(*this, &physics_system::on_acceleration_event);
}
void	physics_system::update()
{
	for (auto& entity : __registered_entities)
	{
		auto&	transform = entity.second.get().component<transform_component>();
		auto&	collision = entity.second.get().component<collision_component>();
		if (transform.velocity.length() <= transform.max_speed)
			transform.velocity += transform.acceleration;
		transform.position += transform.velocity;
		transform.velocity *= 0.5f;
		if (transform.velocity.length() < 1.0f)
			transform.velocity = vector_3(0.0f, 0.0f, 0.0f);
	}
}
void	physics_system::on_collision_event(collision_event& event)
{
	
}
void	physics_system::on_acceleration_event(acceleration_event& event)
{
	auto&	transform = event.entity.component<transform_component>();
	transform.acceleration = event.acceleration;
}

__end_ns_td
