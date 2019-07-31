
#include	"__common.hpp"
#include	"input_system.hpp"
#include	"entity.hpp"
#include	"event_bus.hpp"
#include	"world.hpp"
#include	"sprite.hpp"

__begin_ns_td

void	input_system::start()
{
	world.event_bus.subscribe(*this, &input_system::on_animation_complete_event);
}
void	input_system::update()
{
	auto&	keyboard = world.keyboard;
	auto&	mouse = world.mouse;
	for (auto& entity : __registered_entities)
	{
		auto&	input = entity.second.get().component<input_component>();
		auto&	state = entity.second.get().component<state_component>();
		for (auto& mapping : input.key_mappings)
		{
			if (keyboard.down(mapping.second.first) && keyboard.modifier(mapping.second.second))
			{
				state.state = mapping.first;
				world.event_bus.publish<animation_event>(entity.second.get(), sprite::names.at(state.state));
				switch (state.state)
				{
					case state::right:
						world.event_bus.publish<acceleration_event>(entity.second.get(), vector_3(2.0f, 0.0f, 0.0f));
						break;
					case state::left:
						world.event_bus.publish<acceleration_event>(entity.second.get(), vector_3(-2.0f, 0.0f, 0.0f));
						break;
					case state::attack:
						world.event_bus.publish<acceleration_event>(entity.second.get(), vector_3(0.0f, 0.0f, 0.0f));
						break;
					default:
						break;
				}
			}
			if (keyboard.up(mapping.second.first) && state.state == mapping.first)
			{
				switch (state.state)
				{
					case state::right: case state::left:
						world.event_bus.publish<animation_complete_event>(entity.second.get(), sprite::names.at(state.state));
						world.event_bus.publish<acceleration_event>(entity.second.get(), vector_3(0.0f, 0.0f, 0.0f));
						break;
					default:
						break;
				}
			}
		}
		for (auto& mapping : input.mouse_mappings)
		{
			if (mouse.down(mapping.second.first) && keyboard.modifier(mapping.second.second))
			{
				state.state = mapping.first;
				world.event_bus.publish<animation_event>(entity.second.get(), sprite::names.at(state.state));
				switch (state.state)
				{
					case state::right:
						world.event_bus.publish<acceleration_event>(entity.second.get(), vector_3(2.0f, 0.0f, 0.0f));
						break;
					case state::left:
						world.event_bus.publish<acceleration_event>(entity.second.get(), vector_3(-2.0f, 0.0f, 0.0f));
						break;
					case state::attack:
						world.event_bus.publish<acceleration_event>(entity.second.get(), vector_3(0.0f, 0.0f, 0.0f));
						break;
					default:
						break;
				}
			}
			if (mouse.up(mapping.second.first) && state.state == mapping.first)
			{
				switch (state.state)
				{
					case state::right: case state::left:
						world.event_bus.publish<animation_complete_event>(entity.second.get(), sprite::names.at(state.state));
						break;
					default:
						break;
				}
			}
		}
	}
}
void	input_system::on_animation_complete_event(animation_complete_event& event)
{
	auto&	input = event.entity.component<input_component>();
	auto&	state = event.entity.component<state_component>();
	auto&	render = event.entity.component<render_component>();
	const auto&	__state = sprite::states.at(event.name);
	if (input.key_mappings.count(__state) && !world.keyboard.scan(input.key_mappings.at(__state).first))
	{
		state.state = state::idle;
		render.name = "idle";
		render.flipbooks.at(event.name).reset();
	}
	if (input.mouse_mappings.count(__state) && !world.mouse.scan(input.mouse_mappings.at(__state).first))
	{
		state.state = state::idle;
		render.name = "idle";
		render.flipbooks.at(event.name).reset();
	}
}

__end_ns_td
