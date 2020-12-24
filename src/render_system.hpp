
#pragma once
#include "__common.hpp"
#include "entity.hpp"
#include "exception.hpp"
#include "sprite.hpp"
#include "system.hpp"
#include "window.hpp"

#include <unordered_map>

namespace p201
{

class render_system : public system
{
public:
    using __base = system;

protected:
    SDL_Renderer* __sdl_renderer = nullptr;

    void render_sprite(SDL_Texture*, SDL_Rect*, const vector_2&);

public:
    render_system(class world& world) : __base(world)
    {
        flag.set(component::flag::render);
        flag.set(component::flag::transform);
    }
    virtual ~render_system()
    {
        stop();
    }
    virtual void  start() override;
    void          start(class window&);
    void          stop();
    SDL_Renderer* sdl_renderer()
    {
        return __sdl_renderer;
    }
    virtual void update() override { }
    void         render();

    //	Preventing copying and moving
    render_system(const render_system&) = delete;
    render_system(render_system&&)      = delete;
    render_system& operator=(const render_system&) = delete;
    render_system& operator=(render_system&&) = delete;
};

} // namespace p201
