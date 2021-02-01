
#include "render.hpp"

#include <engine/__common.hpp>

namespace p201
{
namespace systems
{
void render::start()
{
    world.texture_pipeline.load();
}
void render::stop() { }

void render::render_sprite(SDL_Texture* texture, SDL_Rect* src, SDL_FRect* rect)
{
    P201_EVAL_DISCARD(texture);
    P201_EVAL_DISCARD(src);
    P201_EVAL_DISCARD(rect);
}

void render::update(float dt)
{
    __base::update(dt);
}
void render::draw(float alpha)
{
    /* Render all the registered entities one by one. */
    for (auto& id : __registered_entities)
    {
        auto&       entity    = world.entity(id);
        auto&       render    = entity.component<components::render>();
        const auto& transform = entity.component<components::transform>();

        const vector_3 position =
            transform.position * alpha + transform.lerp * (1.0f - alpha);

        const auto screen_position =
            render.iso ? iso_mat * position : forge::reduce(position);

        P201_EVAL_DISCARD(screen_position);

        // render.rect.x = screen_position.x - render.rect.w * render.offset.x;
        // render.rect.y = screen_position.y - render.rect.h * render.offset.y;
        // if (!render.texture)
        //     render.texture =
        //         world.texture_pipeline.default_sprite(render.family);
        if (entity.flag.test(components::camera_focus::flag))
            asm("nop"); // camera.center = util::center(render.rect);
        // if (render.camera) render.rect = camera.transform(render.rect);

        // if (render.visible)
        //     render_sprite(render.texture, &render.srcrect, &render.rect);
    }

    if constexpr (__debug__)
    {
        if (world.keyboard.modifier(forge::modifier::ALT))
        {
            auto& buffer = world.scene.main->getRenderBuffer();
            for (std::size_t i = 0; i < buffer.getNbLines(); ++i)
            {
                const px::PxDebugLine& line = buffer.getLines()[i];

                auto start = camera.transform(iso_mat * convert(line.pos0));
                auto end   = camera.transform(iso_mat * convert(line.pos1));
                P201_EVAL_DISCARD(start);
                P201_EVAL_DISCARD(end);
            }
        }
    }
}
void render::display() { }

} // namespace systems
} // namespace p201
