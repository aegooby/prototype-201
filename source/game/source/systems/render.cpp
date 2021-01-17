
#include "render.hpp"

#include <__common.hpp>

namespace p201
{
namespace systems
{
void render::transform_tile(float x, float y, float w, float h,
                            std::int16_t* vx, std::int16_t* vy)
{
    const vector_2 iso_vec    = iso_23 * vector_3(x, y, 0.0f);
    const vector_2 iso_vec_p1 = iso_23 * vector_3(w, 0.0f, 0.0f);
    const vector_2 iso_vec_p2 = iso_23 * vector_3(w, h, 0.0f);
    const vector_2 iso_vec_p3 = iso_23 * vector_3(0.0f, h, 0.0f);

    vx[0] = iso_vec.x();
    vy[0] = iso_vec.y();

    vx[1] = iso_vec.x() + iso_vec_p1.x();
    vy[1] = iso_vec.y() + iso_vec_p1.y();

    vx[2] = iso_vec.x() + iso_vec_p2.x();
    vy[2] = iso_vec.y() + iso_vec_p2.y();

    vx[3] = iso_vec.x() + iso_vec_p3.x();
    vy[3] = iso_vec.y() + iso_vec_p3.y();
}
void render::render_grid(std::size_t size)
{
    std::int16_t vx[4];
    std::int16_t vy[4];
    for (ssize_t x = -1100; x < 1000; x += size)
    {
        for (ssize_t y = 0; y < 2000; y += size)
        {
            transform_tile(x, y, size, size, vx, vy);
            camera.transform(vx, vy);
            polygonRGBA(__sdl_renderer, vx, vy, 4, 200, 200, 200, 255);
        }
    }
}

void render::start()
{
    std::uint32_t flags = engine::vsync ? SDL_RENDERER_PRESENTVSYNC : 0u;
    __sdl_renderer = SDL_CreateRenderer(world.window.sdl_window(), -1, flags);
    if (!__sdl_renderer) throw sdl_error("Failed to create rendering system");
    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF))
        throw sdl_error("Failed to load SDL Image libraries");
    world.sprite_manager.link(__sdl_renderer);
    world.sprite_manager.load();

    /** @todo This is messy */
    auto& hb_main    = world.hud.healthbar.main;
    hb_main.texture  = world.sprite_manager.flipbook("healthbar", "main").at(0);
    hb_main.position = vector_2(30.0f, 25.0f);
    hb_main.width    = 300.0f;
    hb_main.height   = 30.0f;
    hb_main.rect     = { .x = 0.0f, .y = 0.0f, .w = 300.0f, .h = 30.0f };
    hb_main.srcrect  = { .x = 0, .y = 0, .w = 300, .h = 30 };
}
void render::stop()
{
    SDL_DestroyRenderer(__sdl_renderer);
    __sdl_renderer = nullptr;
    IMG_Quit();
}

void render::render_sprite(SDL_Texture* texture, SDL_Rect* src, SDL_FRect* rect)
{
    if (SDL_RenderCopyF(__sdl_renderer, texture, src, rect))
        throw sdl_error("Failed to render texture");
}

void render::update(float dt)
{
    __base::update(dt);
}
void render::draw(float alpha)
{
    if (SDL_SetRenderDrawColor(__sdl_renderer, 0, 0, 0, 255))
        throw sdl_error("Failed to set draw color");
    if (SDL_RenderClear(__sdl_renderer))
        throw sdl_error("Failed to clear renderer");

    /* Render all the registered entities one by one. */
    for (auto& id : __registered_entities)
    {
        auto&       entity    = world.entity(id);
        auto&       render    = entity.component<components::render>();
        const auto& transform = entity.component<components::transform>();

        const vector_3 position =
            transform.position * alpha + transform.lerp * (1.0f - alpha);

        const auto screen_position =
            render.iso ? iso_23 * position : reduce(position);

        render.rect.x = screen_position.x() - render.rect.w * render.offset.x();
        render.rect.y = screen_position.y() - render.rect.h * render.offset.y();
        if (!render.texture)
            render.texture = world.sprite_manager.default_sprite(render.family);
        if (entity.flag.test(components::camera_focus::flag))
            camera.center = util::center(render.rect);
        if (render.camera) render.rect = camera.transform(render.rect);

        if (render.visible)
            render_sprite(render.texture, &render.srcrect, &render.rect);
    }

    if constexpr (debug)
    {
        if (world.keyboard.modifier(modifier::ALT))
        {
            auto& buffer = world.scene.main->getRenderBuffer();
            for (std::size_t i = 0; i < buffer.getNbLines(); ++i)
            {
                const px::PxDebugLine& line = buffer.getLines()[i];

                auto start = camera.transform(iso_23 * convert(line.pos0));
                auto end   = camera.transform(iso_23 * convert(line.pos1));
                lineRGBA(__sdl_renderer, start.x(), start.y(), end.x(), end.y(),
                         200, 0, 0, 255);
            }
        }
    }

    /* Render the HUD. */
    auto& hb_main  = world.hud.healthbar.main;
    hb_main.rect.x = hb_main.position.x();
    hb_main.rect.y = hb_main.position.y();
    render_sprite(hb_main.texture, &hb_main.srcrect, &hb_main.rect);
}
void render::display()
{
    SDL_RenderPresent(__sdl_renderer);
}

} // namespace systems
} // namespace p201