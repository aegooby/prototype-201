
#include	"__common.hpp"
#include	"physics_system.hpp"
#include	"entity_manager.hpp"
#include	"event.hpp"

__begin_ns_td

bool	physics_system::check_collision(capsule& hitbox_a, capsule& hitbox_b)
{
	float	left_a = hitbox_a.x, left_b = hitbox_b.x;
	float	right_a = hitbox_a.x + hitbox_a.width, right_b = hitbox_b.x + hitbox_b.width;
	float	xcenter_a = hitbox_a.x + hitbox_a.radius();
	float	xcenter_b = hitbox_b.x + hitbox_b.radius();
	float	ytopcenter_a = hitbox_a.y + hitbox_a.height;
	float	ytopcenter_b = hitbox_b.y + hitbox_b.height;
	float	ybotcenter_a = hitbox_a.y;
	float	ybotcenter_b = hitbox_b.y;
	
	float	xdist = std::abs(xcenter_b - xcenter_a);
	
	// If capsule B is above capsule A
	auto	distsquared1 = [xdist, ytopcenter_a, ybotcenter_b]()
	{
		float	ydist = ybotcenter_b - ytopcenter_a;
		return (xdist * xdist) + (ydist * ydist);
	};
	
	// If capsule A is above capsule B
	auto	distsquared2 = [xdist, ybotcenter_a, ytopcenter_b]()
	{
		float	ydist = ybotcenter_a - ytopcenter_b;
		return (xdist * xdist) + (ydist * ydist);
	};
	
	if (right_a >= left_b)
	{
		return true;
	}
	if (right_b <= left_a)
	{
		return true;
	}
	if (distsquared1() <= (hitbox_a.radius() + hitbox_b.radius()) * (hitbox_a.radius() + hitbox_b.radius()))
	{
		return true;
	}
	if (distsquared2() <= (hitbox_b.radius() + hitbox_a.radius()) * (hitbox_b.radius() + hitbox_a.radius()))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void	physics_system::start()
{
	
}
void	physics_system::update()
{
	for (auto& entity : __registered_entities)
	{
		auto&	transform = entity.second.get().component<transform_component>();
		auto&	collision = entity.second.get().component<collision_component>();
		transform.velocity += transform.acceleration;
		transform.position += transform.velocity;
		
	}
}
void	physics_system::on_collision_event(collision_event& event)
{
	
}

__end_ns_td
