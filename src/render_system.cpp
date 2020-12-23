
#include "render_system.hpp"

#include "__common.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "event.hpp"
#include "world.hpp"

// TODO: this file is a mess

namespace p201
{

void render_system::start() { }
void render_system::start(class window& window)
{
    if (!(__sdl_renderer = SDL_CreateRenderer(window.sdl_window(), -1,
                                              SDL_RENDERER_ACCELERATED |
                                                  SDL_RENDERER_PRESENTVSYNC)))
        throw sdl_error("Failed to create render_system");
    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP))
        throw sdl_error("Failed to load SDL Image libraries");
}

void render_system::render_sprite(SDL_Texture* texture, SDL_Rect* rect,
                                  const point_2& location)
{
    SDL_Point center  = { rect->x + (rect->w / 2), rect->y + (rect->h / 2) };
    SDL_Rect  srcrect = { int(location.x), int(location.y), rect->w, rect->h };
    if (SDL_RenderCopyEx(__sdl_renderer, texture, &srcrect, rect, 0.0, &center,
                         SDL_FLIP_NONE))
        throw sdl_error("Failed to render texture");
    // TODO: this is for debugging
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
        auto& render = entity.second.get().component<render_component>();
        SDL_SetRenderDrawColor(__sdl_renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(__sdl_renderer, &render.rect);
    }

    // Hey this is IMPORTANT!
    SDL_RenderPresent(__sdl_renderer);
}

} // namespace p201
