
#pragma once
#include "../__common.hpp"
#include "../camera.hpp"
#include "../entity.hpp"
#include "../exception.hpp"
#include "../quadtree.hpp"
#include "../sprite.hpp"
#include "../window.hpp"
#include "system.hpp"

#include <unordered_map>

namespace p201
{
namespace systems
{
class render : public system
{
public:
    using __base = system;

    sprite::manager sprite_manager;

protected:
    SDL_Renderer* __sdl_renderer = nullptr;
    matrix_3      iso_matrix;
    camera        camera;

private:
    void transform_tile(float, float, float, float, std::int16_t*,
                        std::int16_t*);
    void render_grid(SDL_Renderer*, std::size_t);
    void render_sprite(SDL_Texture*, SDL_Rect*, SDL_FRect*);

    void render_node(const node&, std::int16_t*, std::int16_t*);
    void render_hitbox(const std::unique_ptr<hitbox>&);

public:
    render(class world& world) : __base(world), sprite_manager("sprites")
    {
        flag.set(components::render::flag);
        flag.set(components::transform::flag);
    }
    virtual ~render()
    {
        stop();
    }

    void render_quadtree(const quadtree&);

    virtual void  start() override;
    void          stop();
    SDL_Renderer* sdl_renderer()
    {
        return __sdl_renderer;
    }
    virtual void update() override;
    void         display();

    // Preventing copying and moving
    render(const render&) = delete;
    render(render&&)      = delete;
    render& operator=(const render&) = delete;
    render& operator=(render&&) = delete;
};
} // namespace systems
} // namespace p201
