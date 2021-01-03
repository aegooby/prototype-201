
#pragma once
#include "__common.hpp"
#include "clock.hpp"
#include "entity_manager.hpp"
#include "event.hpp"
#include "input.hpp"
#include "serialize.hpp"
#include "system.hpp"
#include "window.hpp"
#include "world.hpp"

#include <chrono>
#include <thread>

namespace p201
{

class engine
{
protected:
    window    window;
    keyboard& keyboard;
    mouse&    mouse;
    clock     clock;
    world     world;

    bool        __running        = false;
    const float fps              = 60.0f;
    const float __time_per_frame = 1.0f / fps;

    /** @brief Checks for CMD-W or CTRL-W to close the window. */
    bool window_close_key() const
    {
#if defined(P201_OS_MACOS)
        return (keyboard.down(keycode::W) && keyboard.modifier(modifier::GUI));
#elif defined(P201_OS_WINDOWS)
        return (keyboard.down(keycode::W) && keyboard.modifier(modifier::CTRL));
#else
        return false;
#endif
    }

public:
    engine()
        : window("Prototype 201"),
          keyboard(window.keyboard),
          mouse(window.mouse),
          world(window, keyboard, mouse)
    {
        window.start();
        for (auto& system : world.systems) system.second->start();

        world.serializer.directory = "entities";
        world.serializer.load_entity(world.new_entity(), "player");
        world.serializer.load_entity(world.new_entity(), "platform");
    }
    ~engine() = default;
    void start()
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

            /* Set time for "this iteration" */
            float time_next_it     = clock.time_s();
            float time_taken_frame = time_next_it - time_last_it;

            time_last_it = time_next_it;

            /* To count the time that has passed from one iteration to the next
             */
            time_unprocessed += time_taken_frame;
            __frame_time += time_taken_frame;

            /* Check frame rate */
            if (__frame_time >= __frame_rate_check)
            {
                __frame_time  = 0;
                __frame_count = 0;
            }

            /*
             * Process anything that has happened in the last one or more frames
             * This avoids input lag and gives the engine a chance to catch up
             * on input/logic before trying to render
             */

            /* This all made sense to me at some point */

            while (time_unprocessed >= __time_per_frame)
            {
                /* All non-graphical processing */
                if (window.closed()) __running = false;

                update(__time_per_frame * global::fpsfactor);

                /* One frame has been rendered, so subtract */
                time_unprocessed -= __time_per_frame;

                /* Once this loop is done, we will be ready to render */
                render_ready = true;
            }
            /* Render a frame */
            if (render_ready)
            {
                display();
                if (window_close_key()) stop();

                /* Every time a frame is rendered successfully */
                __frame_count++;
            }
            else
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    void start_other()
    {
        if (__running) return;
        __running = true;

        const float __dt      = 1.0f / fps;
        float       time_prev = clock.time_s();

        while (__running)
        {
            bool render_ready = false;

            /* Set time for "this iteration" */
            float time_next  = clock.time_s();
            float time_frame = time_next - time_prev;
            time_prev        = time_next;

            /* This all made sense to me at some point */

            while (time_frame > 0.0f)
            {
                if (window.closed()) __running = false;

                float __delta = std::min(time_frame, __dt);
                std::cout << "__dt: " << __dt << std::endl;
                std::cout << "time_frame: " << time_frame << std::endl;
                update(__dt);

                time_frame -= __delta;
                render_ready = true;
            }
            /* Render a frame */
            if (render_ready)
            {
                display();
                if (window_close_key()) stop();
            }
            else
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    void stop()
    {
        __running = false;
    }
    void display()
    {
        world.system<systems::render>().display();
    }
    void update(float dt)
    {
        window.update();
        for (auto& system : world.systems) system.second->update(dt);
    }

    // Preventing copying and moving
    engine(const engine&) = delete;
    engine(engine&&)      = delete;
    engine& operator=(const engine&) = delete;
    engine& operator=(engine&&) = delete;
};

} // namespace p201
