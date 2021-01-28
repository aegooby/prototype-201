
#include "engine.hpp"

namespace p201
{
engine::engine() : world(keyboard, mouse)
{
    forge::sdl::start();
    window.start();
    vulkan.start();
}
engine::~engine()
{
    forge::sdl::stop();
}
void engine::start()
{
    if (__running) return;
    __running = true;

    for (auto& system : world.systems) system.second->start();

    double time_prev   = clock.time_s();
    double accumulator = 0.0;

    while (__running)
    {
        bool idle = true;

        const double time_next  = clock.time_s();
        const double time_frame = time_next - time_prev;

        time_prev = time_next;
        accumulator += time_frame;

        while (accumulator >= dt)
        {
            if (!window.open()) __running = false;
            update(dt);
            accumulator -= dt;
            idle = false;
        }
        if (!idle)
        {
            const double alpha = accumulator / dt;
            render(alpha);
            if (keyboard.window_close()) stop();
        }
        else
            util::sleep(1);
    }
}
void engine::stop()
{
    __running = false;
}
void engine::update(float dt)
{
    window.update();
    for (auto& system : world.systems) system.second->update(dt);
    world.scene.main->simulate(dt);
    world.scene.main->fetchResults(true);
}
void engine::render(float alpha)
{
    render_function(alpha);
    vulkan.draw();
}
void engine::bind_render_function(const std::function<void(float)>& function)
{
    render_function = function;
}
} // namespace p201