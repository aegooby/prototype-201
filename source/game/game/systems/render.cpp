
#include "render.hpp"

#include <__common.hpp>

namespace p201
{
namespace systems
{
void render::start()
{
    std::uint32_t flags = engine::vsync ? SDL_RENDERER_PRESENTVSYNC : 0u;
    handle              = SDL_CreateRenderer(world.window.handle, -1, flags);
    if (!handle) throw sdl_error("Failed to create rendering system");
    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF))
        throw sdl_error("Failed to load SDL Image libraries");
    world.texture_pipeline.link(handle);
    world.texture_pipeline.load();

    /** @todo This is messy. */
    auto& hb_main = world.hud.healthbar.main;
    hb_main.texture =
        world.texture_pipeline.flipbook("healthbar", "main").at(0);
    hb_main.position = vector_2(30.0f, 25.0f);
    hb_main.width    = 300.0f;
    hb_main.height   = 30.0f;
    hb_main.rect     = { .x = 0.0f, .y = 0.0f, .w = 300.0f, .h = 30.0f };
    hb_main.srcrect  = { .x = 0, .y = 0, .w = 300, .h = 30 };
}
void render::stop()
{
    SDL_DestroyRenderer(handle);
    handle = nullptr;
    IMG_Quit();
}

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
            render.iso ? iso_mat * position : reduce(position);

        render.rect.x = screen_position.x - render.rect.w * render.offset.x;
        render.rect.y = screen_position.y - render.rect.h * render.offset.y;
        if (!render.texture)
            render.texture =
                world.texture_pipeline.default_sprite(render.family);
        if (entity.flag.test(components::camera_focus::flag))
            camera.center = util::center(render.rect);
        if (render.camera) render.rect = camera.transform(render.rect);

        if (render.visible)
            render_sprite(render.texture, &render.srcrect, &render.rect);
    }

    if constexpr (__debug__)
    {
        if (world.keyboard.modifier(modifier::ALT))
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

    /* Render the HUD. */
    auto& hb_main  = world.hud.healthbar.main;
    hb_main.rect.x = hb_main.position.x;
    hb_main.rect.y = hb_main.position.y;
    render_sprite(hb_main.texture, &hb_main.srcrect, &hb_main.rect);
}
void render::display() { }

} // namespace systems
} // namespace p201
