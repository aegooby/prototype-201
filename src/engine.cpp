
#include "engine.hpp"

#include "__common.hpp"
#include "clock.hpp"
#include "component_manager.hpp"
#include "event.hpp"
#include "input_system.hpp"
#include "physics_system.hpp"
#include "render_system.hpp"
#include "window.hpp"

#include <chrono>
#include <thread>
#include <unordered_map>

namespace p201
{

engine::engine(const std::string& title, int width, int height, bool fpsdebug)
    : window(title, width, height),
      keyboard(window.keyboard),
      mouse(window.mouse),
      world(keyboard, mouse),
      __fpsdebug(fpsdebug)
{
    window.start();
    for (auto& system : world.systems) { system.second->start(); }
    world.system<render_system>().start(window);
    auto& player = world.new_entity(entity_type::player);
    player.add_component<render_component>();
    player.add_component<transform_component>();
    player.add_component<collision_component>();
    player.add_component<input_component>();
    player.add_component<state_component>();
    player.component<transform_component>().position = vector_3(100, 100, 0);
    player.component<render_component>().rect.w      = 160;
    player.component<render_component>().rect.h      = 132;
    world.system<render_system>().load("/Users/admin/Desktop/sprites/");
}

bool engine::cmd_w() const
{
#if defined(TD_OS_MACOS)
    return (keyboard.down(keycode::W) && keyboard.modifier(modifier::GUI));
#elif defined(TD_OS_WINDOWS)
    return (keyboard.down(keycode::W) && keyboard.modifier(modifier::CTRL));
#else
    return false;
#endif
}

void engine::start()
{
    if (__running) return;
    __running = true;

    float time_last_it     = clock.time_s();
    float time_unprocessed = 0;

    int32_t     __frame_count      = 0;
    float       __frame_time       = 0;
    const float __frame_rate_check = 1.0f;

    while (__running)
    {
        bool render_ready = false;

        //	Set time for "this iteration"
        float time_next_it     = clock.time_s();
        float time_taken_frame = time_next_it - time_last_it;

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
            __frame_time  = 0;
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
            if (window.closed()) __running = false;

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
            if (cmd_w()) { stop(); }

            //	Every time a frame is rendered successfully
            __frame_count++;
        }
        else
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
void engine::stop()
{
    __running = false;
}
void engine::render()
{
    world.system<render_system>().render();
}
void engine::update()
{
    // Input
    window.update();
    for (auto& system : world.systems) { system.second->update(); }
}

} // namespace p201
