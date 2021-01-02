
#pragma once
#include "../__common.hpp"
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

private:
    void transform_tile(float x, float y, float w, float h, std::int16_t* vx,
                        std::int16_t* vy);
    void render_grid(SDL_Renderer*, std::size_t);
    void render_sprite(SDL_Texture*, SDL_FRect*);

    void render_node(const node&, std::int16_t*, std::int16_t*);
    void render_hitbox(const std::unique_ptr<hitbox>&);

    vector_3  camera_transform(const vector_3&);
    SDL_FRect camera_transform(const SDL_FRect&);
    void      camera_transform(std::int16_t*, std::int16_t*);

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
