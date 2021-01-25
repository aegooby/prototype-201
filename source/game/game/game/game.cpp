
#include "game.hpp"

#include "../components.hpp"
#include "../events.hpp"
#include "../systems.hpp"

namespace p201
{
game::game()
{
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

    auto render_function = [this](float alpha)
    {
        engine.world.system<p201::systems::render>().draw(alpha);
        engine.world.system<p201::systems::render>().display();
    };
    engine.bind_render_function(render_function);

    engine.start();
}
game::~game() = default;
} // namespace p201