
#include "engine.hpp"

#include <game.hpp>
#include <vulkan.hpp>

namespace p201
{
engine::engine()
    : window("Prototype 201"),
      keyboard(window.keyboard),
      mouse(window.mouse),
      world(window, keyboard, mouse)
{
    window.start();
    vulkan::create_instance(window.sdl_window());
    vulkan::create_surface(window.sdl_window());
    for (auto& system : world.systems) system.second->start();

    world.serializer.directory = "assets/entities";
    world.serializer.load_entity(world.new_entity(), "player");
    world.serializer.load_entity(world.new_entity(), "platform");
}
void engine::start()
{
    if (__running) return;
    __running = true;

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
    world.system<systems::render>().draw(alpha);
    world.system<systems::render>().display();
}
} // namespace p201