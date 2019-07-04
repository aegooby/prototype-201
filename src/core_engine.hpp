
#pragma	once
#include	"__common.hpp"
#include	"window.hpp"
#include	"clock.hpp"
#include	"renderer.hpp"
#include	"entity.hpp"
#include	"newton.hpp"
#include	"event.hpp"
#include	<thread>
#include	<chrono>
#include	<list>

__begin_ns_td

class	core_engine
{
protected:
	td::window			window;
	td::renderer		renderer;
	td::keyboard&		keyboard;
	td::mouse&			mouse;
	td::clock			clock;
	td::newton			newton;
	td::event_handler	event_handler;
	std::list<std::unique_ptr<entity>>	entities;
	bool		__running = false, __fpsdebug = false;
	const float	__time_per_frame = 1.0f / float(global::game_fps);
	
	bool	cmd_w() const
	{
#if	defined(TD_OS_MACOS)
		return (keyboard.down(keycode::W) && keyboard.modifier(modifier::GUI));
#else
		return false;
#endif
	}
public:
	core_engine(const std::string& title, int width, int height, bool fpsdebug) : window(title, width, height), renderer(window), keyboard(window.keyboard), mouse(window.mouse), __fpsdebug(fpsdebug)
	{
		window.start();
		renderer.start();
		add_entity(std::make_unique<td::character>(event_handler));
		dynamic_cast<td::character*>(entities.back().get())->render->add_child(std::make_unique<sprite_flipbook>("stand", 10.0f));
		dynamic_cast<td::character*>(entities.back().get())->render->rect(100, 100, 100, 74);
		dynamic_cast<td::character*>(entities.back().get())->render->children().at("stand")->create(renderer, "/Users/admin/Desktop/atk");
	}
	~core_engine() = default;
	void	start()
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
	void	stop()
	{
		__running = false;
	}
	void	render()
	{
		renderer.render(entities);
	}
	void	update()
	{
		// Input
		window.update();
//		for (auto& entity : entities)
//		{
//			entity->update();
//		}
	}
	void	add_entity(std::unique_ptr<entity>&& entity)
	{
		entities.emplace_back(std::forward<decltype(entity)>(entity));
	}
	void	remove_entity(const std::unique_ptr<entity>& entity)
	{
		entities.remove_if([&entity](const std::unique_ptr<td::entity>& __entity)
						   {
							   return &__entity == &entity;
						   });
	}
	
	//	Preventing copying and moving
	core_engine(const core_engine&) = delete;
	core_engine(core_engine&&) = delete;
	core_engine&	operator =(const core_engine&) = delete;
	core_engine&	operator =(core_engine&&) = delete;
};

__end_ns_td
