
#include "engine.hpp"

namespace p201
{
engine::engine()
    : window("Prototype 201"),
      keyboard(window.keyboard),
      mouse(window.mouse),
      world(window, keyboard, mouse)
{
    window.start();
    vulkan.create_instance(window.handle);
    vulkan.create_surface(window.handle);
    vulkan.create_device();
    vulkan.create_swapchain(window.handle);
    vulkan.create_pipeline();
    vulkan.create_framebuffers();
    vulkan.create_command_pool();
    vulkan.create_command_buffers();
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
            if (window.closed()) __running = false;
            update(dt);
            accumulator -= dt;
            idle = false;
        }
        if (!idle)
        {
            const double alpha = accumulator / dt;
            render(alpha);
            if (window_close_key()) stop();
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