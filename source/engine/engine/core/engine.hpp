
#pragma once
#include "../ecs.hpp"
#include "../event.hpp"
#include "../physx.hpp"
#include "../util.hpp"
#include "world.hpp"

#include <__common.hpp>
#include <forge.hpp>
#include <functional>
#include <thread>

namespace p201
{

class engine
{
public:
    static constexpr double dt    = 1.0 / 60.0;
    static constexpr bool   vsync = true;

private:
    std::function<void(float)> render_function;

protected:
    forge::keyboard keyboard = forge::keyboard();
    forge::mouse    mouse    = forge::mouse();
    forge::window   window   = forge::window(keyboard, mouse, "Prototype 201");
    forge::rhi      vulkan   = forge::rhi(engine::window);

    clock clock;

    bool  __running = false;
    float fps       = 60.0f;

public:
    world world;

public:
    engine();
    ~engine();
    void start();
    void stop();
    void update(float dt);
    void render(float alpha);

    void bind_render_function(const std::function<void(float)>&);

    engine(const engine&) = delete;
    engine(engine&&)      = delete;
    engine& operator=(const engine&) = delete;
    engine& operator=(engine&&) = delete;
};

} // namespace p201
