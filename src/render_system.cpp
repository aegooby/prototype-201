
#include "render_system.hpp"

#include "__common.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "event.hpp"
#include "linalg.hpp"
#include "world.hpp"

namespace p201
{

// TODO: this is a temporary function
static void iso_tile(const vector_3& vec, const matrix_3& matrix,
                     SDL_FRect& rect, std::int16_t* vx, std::int16_t* vy)
{
    vector_3 iso_vec    = matrix * vec;
    vector_3 iso_vec_p1 = matrix * vector_3(rect.w, 0.0f, 0.0f);
    vector_3 iso_vec_p2 = matrix * vector_3(rect.w, rect.h, 0.0f);
    vector_3 iso_vec_p3 = matrix * vector_3(0.0f, rect.h, 0.0f);

    vx[0] = iso_vec.x();
    vy[0] = iso_vec.y();

    vx[1] = iso_vec.x() + iso_vec_p1.x();
    vy[1] = iso_vec.y() + iso_vec_p1.y();

    vx[2] = iso_vec.x() + iso_vec_p2.x();
    vy[2] = iso_vec.y() + iso_vec_p2.y();

    vx[3] = iso_vec.x() + iso_vec_p3.x();
    vy[3] = iso_vec.y() + iso_vec_p3.y();
}

void render_system::start()
{
    iso_matrix << 1.0f, -1.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, sqrt_2;
    // flipped:
    // iso_matrix << -1.0f, 1.0f, 0.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, sqrt_2;
    iso_matrix /= sqrt_2;
}
void render_system::start(class window& window)
{
    if (!(__sdl_renderer = SDL_CreateRenderer(window.sdl_window(), -1,
                                              SDL_RENDERER_ACCELERATED |
                                                  SDL_RENDERER_PRESENTVSYNC)))
        throw sdl_error("Failed to create render_system");
    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP))
        throw sdl_error("Failed to load SDL Image libraries");
}
void render_system::stop()
{
    if (__sdl_renderer)
    {
        SDL_DestroyRenderer(__sdl_renderer);
        __sdl_renderer = nullptr;
    }
    IMG_Quit();
}

void render_system::render_sprite(SDL_Texture* texture, SDL_Rect* rect,
                                  const vector_2& location)
{
    SDL_Point center  = { rect->x + (rect->w / 2), rect->y + (rect->h / 2) };
    SDL_Rect  srcrect = { int(location.x()), int(location.y()), rect->w,
                         rect->h };
    if (SDL_RenderCopyEx(__sdl_renderer, texture, &srcrect, rect, 0.0, &center,
                         SDL_FLIP_NONE))
        throw sdl_error("Failed to render texture");
    SDL_SetRenderDrawColor(__sdl_renderer, 0, 255, 0, 255);
    SDL_Rect center_rect = { center.x - 2, center.y - 2, 4, 4 };
    SDL_RenderFillRect(__sdl_renderer, &center_rect);
}

void render_system::render()
{
    if (SDL_SetRenderDrawColor(__sdl_renderer, 0, 0, 0, 255))
        throw sdl_error("Failed to set draw color");
    if (SDL_RenderClear(__sdl_renderer))
        throw sdl_error("Failed to clear render_system");

    // Render all the registered entities one by one
    for (auto& entity : __registered_entities)
    {
        auto& render    = entity.second.get().component<render_component>();
        auto& transform = entity.second.get().component<transform_component>();
        (void)render;
        (void)transform;

        // TODO: this is a temporary setup to test the isometric rendering
        std::int16_t vx[4], vy[4];
        iso_tile(transform.position, iso_matrix, render.rect, vx, vy);
        filledPolygonRGBA(__sdl_renderer, vx, vy, 4, 255, 255, 255, 255);
        polygonRGBA(__sdl_renderer, vx, vy, 4, 255, 0, 0, 255);
    }

    // Hey this is IMPORTANT!
    SDL_RenderPresent(__sdl_renderer);
}

} // namespace p201
