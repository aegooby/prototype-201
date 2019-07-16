
#include	"__common.hpp"
#include	"engine.hpp"
#include	"window.hpp"
#include	"clock.hpp"
#include	"renderer.hpp"
#include	"newton.hpp"
#include	"event.hpp"
#include	"component_manager.hpp"
#include	<thread>
#include	<chrono>
#include	<unordered_map>

__begin_ns_td

engine::engine(const std::string& title, int width, int height, bool fpsdebug) : window(title, width, height), keyboard(window.keyboard), mouse(window.mouse), renderer(world, window), newton(world), entity_manager(world), __fpsdebug(fpsdebug)
{
	window.start();
	renderer.start();
	entity_manager.add_entity("player");
	auto&	player = *entity_manager.entities.at(0);
	player.add_component<render_component>();
//	transform_manager.add_component(*entities.at("player"), "transform");
//	renderer.load(entities, "/Users/admin/Desktop/sprites");
}

bool	engine::cmd_w() const
{
#if		defined(TD_OS_MACOS)
	return (keyboard.down(keycode::W) && keyboard.modifier(modifier::GUI));
#elif	defined(TD_OS_WINDOWS)
	return (keyboard.down(keycode::W) && keyboard.modifier(modifier::CTRL));
#else
	return false;
#endif
}

void	engine::start()
{
	if (__running) return;
	__running = true;
	
	float	time_last_it = clock.time_s();
	float	time_unprocessed = 0;
	
	int32_t		__frame_count = 0;
	float		__frame_time = 0;
	const float	__frame_rate_check = 1.0f;
	
	while (__running)
	{
		bool	render_ready = false;
		
		//	Set time for "this iteration"
		float	time_next_it = clock.time_s();
		float	time_taken_frame = time_next_it - time_last_it;
		
		time_last_it = time_next_it;
		
		//	To count the time that has passed from one iteration to the next
		time_unprocessed += time_taken_frame;
		__frame_time += time_taken_frame;
		
		// Check frame rate
		if (__frame_time >= __frame_rate_check)
		{
			if (__fpsdebug)
			{
				std::cout << "fps: ";
				std::cout << float(__frame_count) / __frame_rate_check;
				std::cout << std::endl;
			}
			__frame_time = 0;
			__frame_count = 0;
		}
		
		// Process anything that has happened in the last one or more frames
		// This avoids input lag and gives the engine a chance to catch up
		// on input/logic before trying to render
		// (Prefer visual lag over logic lag)
		
		// This all made sense to me at some point
		
		while (time_unprocessed >= __time_per_frame)
		{
			//	All non-graphical processing
			if (window.closed())
				__running = false;
			
			update();
			
			//	One frame has been rendered, so subtract
			time_unprocessed -= __time_per_frame;
			
			//	Once this loop is done, we will be ready to render everything
			render_ready = true;
		}
		//	Render a frame
		if (render_ready)
		{
			render();
			if (cmd_w())
			{
				stop();
			}
			
			//	Every time a frame is rendered successfully
			__frame_count++;
		}
		else
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
void	engine::stop()
{
	__running = false;
}
void	engine::render()
{
//	renderer.render(entities);
}
void	engine::update()
{
	// Input
	window.update();
//	newton.update(entities);
}

__end_ns_td
