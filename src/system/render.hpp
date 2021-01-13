
#pragma once
#include "../__common.hpp"
#include "../camera.hpp"
#include "../entity.hpp"
#include "../exception.hpp"
#include "../window.hpp"
#include "system.hpp"

#include <unordered_map>

#define P201_ISO_23 1.0f, 1.0f, 0.0f, -0.5f, 0.5f, -1.0f

namespace p201
{
namespace systems
{
class render : public system
{
public:
    using __base = system;

protected:
    SDL_Renderer*   __sdl_renderer = nullptr;
    const matrix_23 iso_23 = (matrix_23() << P201_ISO_23).finished() / sqrt_2;
    /** @brief How many times do I have to tell you
       to read the name retard? */
    camera camera;

private:
    void transform_tile(float, float, float, float, std::int16_t*,
                        std::int16_t*);
    void render_grid(std::size_t);
    void render_sprite(SDL_Texture*, SDL_Rect*, SDL_FRect*);

public:
    render(class world& world) : __base(world)
    {
        flag.set(components::render::flag);
        flag.set(components::transform::flag);
    }
    virtual ~render() override
    {
        stop();
    }

    virtual void start() override;
    void         stop();
    virtual void update(float dt) override;
    void         draw(float alpha);
    void         display();

    render(const render&) = delete;
    render(render&&)      = delete;
    render& operator=(const render&) = delete;
    render& operator=(render&&) = delete;
};
} // namespace systems
} // namespace p201
