
#include "render.hpp"

#include "../__common.hpp"
#include "../entity.hpp"
#include "../entity_manager.hpp"
#include "../event.hpp"
#include "../linalg.hpp"
#include "../util.hpp"
#include "../window.hpp"
#include "../world.hpp"

namespace p201
{
namespace systems
{
// TODO: this is a temporary function
void render::iso_tile(const vector_3& vec, std::size_t w, std::size_t h,
                      std::int16_t* vx, std::int16_t* vy)
{
    vector_3 iso_vec    = iso_matrix * vec;
    vector_3 iso_vec_p1 = iso_matrix * vector_3(w, 0.0f, 0.0f);
    vector_3 iso_vec_p2 = iso_matrix * vector_3(w, h, 0.0f);
    vector_3 iso_vec_p3 = iso_matrix * vector_3(0.0f, h, 0.0f);

    vx[0] = iso_vec.x();
    vy[0] = iso_vec.y();

    vx[1] = iso_vec.x() + iso_vec_p1.x();
    vy[1] = iso_vec.y() + iso_vec_p1.y();

    vx[2] = iso_vec.x() + iso_vec_p2.x();
    vy[2] = iso_vec.y() + iso_vec_p2.y();

    vx[3] = iso_vec.x() + iso_vec_p3.x();
    vy[3] = iso_vec.y() + iso_vec_p3.y();
}
void render::render_grid_tile(SDL_Renderer* renderer, std::size_t size,
                              std::uint8_t alpha)
{
    std::int16_t vx[4];
    std::int16_t vy[4];
    for (ssize_t x = -1100; x < 1000; x += size)
    {
        for (ssize_t y = 0; y < 2000; y += size)
        {
            iso_tile(vector_3(x, y, 0.0f), size, size, vx, vy);
            polygonRGBA(__sdl_renderer, vx, vy, 4, 200, 200, 200, alpha);
        }
    }
}
void render::render_grid_line(SDL_Renderer* renderer, std::size_t size,
                              std::uint8_t alpha)
{
    static const std::size_t tile_y = (float(size) / sqrt_2);
    static const std::size_t tile_x = (float(size) * sqrt_2);

    vector_3 vec = iso_matrix * vector_3(window::width * 3, 0.0f, 0.0f);
    for (ssize_t i = 0; i < 2 * window::height; i += tile_y)
    {
        float y = float(i);
        lineRGBA(renderer, 0, y, vec.x(), vec.y() + y, 200, 200, 200, alpha);
    }
    vec = iso_matrix * vector_3(0.0f, window::height * 3, 0.0f);
    for (ssize_t i = -window::width; i < window::width; i += tile_x)
    {
        float x = float(i);
        lineRGBA(renderer, x, 0, vec.x() + x, vec.y(), 200, 200, 200, alpha);
    }
}

void render::start()
{
    // TODO: element [2, 3] might be wrong
    iso_matrix << 1.0f, 1.0f, 0.0f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f;
    iso_matrix /= sqrt_2;
    if (!(__sdl_renderer = SDL_CreateRenderer(world.window.sdl_window(), -1,
                                              SDL_RENDERER_PRESENTVSYNC)))
        throw sdl_error("Failed to create rendering system");
    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF))
        throw sdl_error("Failed to load SDL Image libraries");
    world.sprite_manager.link(__sdl_renderer);
}
void render::stop()
{
    if (__sdl_renderer)
    {
        SDL_DestroyRenderer(__sdl_renderer);
        __sdl_renderer = nullptr;
    }
    IMG_Quit();
}

void render::render_sprite(SDL_Texture* texture, SDL_FRect* rect)
{
    if (SDL_RenderCopyF(__sdl_renderer, texture, NULL, rect))
        throw sdl_error("Failed to render texture");
}

void render::render_frame()
{
    if (SDL_SetRenderDrawColor(__sdl_renderer, 0, 0, 0, 255))
        throw sdl_error("Failed to set draw color");
    if (SDL_RenderClear(__sdl_renderer))
        throw sdl_error("Failed to clear renderer");

    // TODO: this is laggy as fuck
    debug(render_grid_tile(__sdl_renderer, 100, 200));

    // Render all the registered entities one by one
    for (auto& ref_pair : __registered_entities)
    {
        auto&       entity    = ref_pair.second.get();
        auto&       render    = entity.component<components::render>();
        const auto& transform = entity.component<components::transform>();

        const vector_3 iso_position = iso_matrix * transform.position;

        render.rect.x = iso_position.x() - render.rect.w / 2;
        render.rect.y = iso_position.y() - render.rect.h / 2;

        // If a texture hasn't been loaded, use the still at the start
        // of the flipbook.
        if (!render.texture)
            render.texture = world.sprite_manager.default_sprite(render.family);

        render_sprite(render.texture, &render.rect);
    }

    SDL_RenderPresent(__sdl_renderer);
}
} // namespace systems
} // namespace p201
