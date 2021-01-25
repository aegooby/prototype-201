
#include <__common.hpp>
#include <core.hpp>
#include <game.hpp>

#if defined(main)
#    undef main
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    p201::engine engine;
    if constexpr (p201::__debug__) { p201::__print_header__(); }
    engine.world.create_component<p201::components::render>();
    engine.world.create_component<p201::components::transform>();
    engine.world.create_component<p201::components::character>();
    engine.world.create_component<p201::components::physics>();
    engine.world.create_component<p201::components::input>();
    engine.world.create_component<p201::components::animation>();
    engine.world.create_component<p201::components::camera_focus>();
    engine.world.create_component<p201::components::health>();
    engine.world.create_component<p201::components::attack>();
    engine.world.create_component<p201::components::hud>();

    engine.world.create_system<p201::systems::render>();
    engine.world.create_system<p201::systems::physics>();
    engine.world.create_system<p201::systems::input>();
    engine.world.create_system<p201::systems::animation>();
    engine.world.create_system<p201::systems::combat>();
    engine.world.create_system<p201::systems::character>();

    auto render_function = [&engine](float alpha)
    {
        engine.world.system<p201::systems::render>().draw(alpha);
        engine.world.system<p201::systems::render>().display();
    };
    engine.bind_render_function(render_function);

    engine.start();

    return 0;
}
