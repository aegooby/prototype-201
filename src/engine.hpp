
#pragma once
#include "__common.hpp"
#include "clock.hpp"
#include "entity_manager.hpp"
#include "event.hpp"
#include "input.hpp"
#include "physics_system.hpp"
#include "window.hpp"
#include "world.hpp"

namespace p201
{

class engine
{
    protected:
    window      window;
    keyboard&   keyboard;
    mouse&      mouse;
    clock       clock;
    world       world;
    bool        __running = false, __fpsdebug = false;
    const float __time_per_frame = 1.0f / float(global::game_fps);

    protected:
    bool cmd_w() const;

    public:
    engine(const std::string&, int, int, bool);
    ~engine() = default;
    void start();
    void stop();
    void render();
    void update();

    //	Preventing copying and moving
    engine(const engine&) = delete;
    engine(engine&&)      = delete;
    engine& operator=(const engine&) = delete;
    engine& operator=(engine&&) = delete;
};

} // namespace p201
