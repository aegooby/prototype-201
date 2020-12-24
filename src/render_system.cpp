
#include "render_system.hpp"

#include "__common.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "event.hpp"
#include "linalg.hpp"
#include "world.hpp"

namespace p201
{

static const float sqrt_2 = std::sqrt(2.0f);
static const float sqrt_3 = std::sqrt(3.0f);
static const float sqrt_6 = std::sqrt(6.0f);

void render_system::start()
{
    iso_matrix.at_element(0, 0) = sqrt_3;
    iso_matrix.at_element(0, 1) = 0;
    iso_matrix.at_element(0, 2) = -sqrt_3;
    iso_matrix.at_element(1, 0) = 1;
    iso_matrix.at_element(1, 1) = 2;
    iso_matrix.at_element(1, 2) = 1;
    iso_matrix.at_element(2, 0) = sqrt_2;
    iso_matrix.at_element(2, 1) = -sqrt_2;
    iso_matrix.at_element(2, 2) = sqrt_2;

    iso_matrix /= sqrt_6;
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
    SDL_Point center = { rect->x + (rect->w / 2), rect->y + (rect->h / 2) };
    SDL_Rect srcrect = { int(location[0]), int(location[1]), rect->w, rect->h };
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
        auto  iso_position =
            boost::numeric::ublas::prod(iso_matrix, transform.position);
        render.rect.x = iso_position(0);
        render.rect.y = iso_position(1);
        SDL_SetRenderDrawColor(__sdl_renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(__sdl_renderer, &render.rect);
    }

    // Hey this is IMPORTANT!
    SDL_RenderPresent(__sdl_renderer);
}

} // namespace p201
