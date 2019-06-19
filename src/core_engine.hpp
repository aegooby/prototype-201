
#pragma	once
#include	"__common.hpp"
#include	"window.hpp"
#include	"clock.hpp"
#include	"renderer.hpp"
#include	"entity.hpp"
#include	"newton.hpp"
#include	<thread>
#include	<chrono>
#include	<list>

__begin_ns_td

class	core_engine
{
protected:
	td::window		window;
	td::renderer	renderer;
	td::keyboard&	keyboard;
	td::mouse&		mouse;
	td::clock		clock;
	td::newton		newton;
	std::list<std::unique_ptr<entity>>	entities;
	bool		__running = false;
	const float	__time_per_frame = 1.0f / 60.0f;
	
	bool	cmd_w() const
	{
		return (keyboard.key_scan(keycode::W) && (keyboard.key_scan(keycode::LGUI) || keyboard.key_scan(keycode::RGUI)));
	}
public:
	core_engine(const std::string& title, int width, int height) : window(title, width, height), renderer(window), keyboard(window.keyboard), mouse(window.mouse)
	{
		window.start();
		renderer.start();
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
				std::cout << "fps: ";
				std::cout << float(__frame_count) / __frame_rate_check;
				std::cout << std::endl;
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
				
				// This takes in all the input
				window.update();
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
//		for (auto& entity : entities)
//		{
//			entity->update();
//		}
	}
	void	add_object(std::unique_ptr<entity>&& entity)
	{
		entities.emplace_back(std::forward<decltype(entity)>(entity));
	}
	void	remove_object(std::unique_ptr<entity>& entity)
	{
		entities.erase(std::remove_if(entities.begin(), entities.end(),
									  [&entity](decltype(entity) __entity)
									  {
										  return __entity == entity;
									  }));
	}
	
	//	Preventing copying and moving
	core_engine(const core_engine&) = delete;
	core_engine(const core_engine&&) = delete;
	core_engine&	operator =(const core_engine&) = delete;
	core_engine&	operator =(const core_engine&&) = delete;
};

__end_ns_td
