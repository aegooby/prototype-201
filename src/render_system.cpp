
#include "render_system.hpp"

#include "__common.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "event.hpp"
#include "filesystem.hpp"
#include "world.hpp"

// TODO: this file is a mess

namespace p201
{

const std::unordered_map<entity_type, std::string>
    render_system::spritesheet_names = {
        { entity_type::player, "player" },
    };

void render_system::start()
{
    world.event_bus.subscribe(*this, &render_system::on_animation_event);
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
void render_system::load_flipbook(render_component& render, float fps,
                                  const sprite_info& info)
{
}

void render_system::load(const std::string& path)
{
    std::string __path = path;
    if (__path.back() != P201_DIRECTORY_SLASH) __path += P201_DIRECTORY_SLASH;
    //        IMG_LoadTexture()
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

void render_system::render_flipbook(class entity&    entity,
                                    sprite_flipbook& flipbook, SDL_Rect* rect)
{
}

void render_system::render()
{
    if (SDL_SetRenderDrawColor(__sdl_renderer, 0, 0, 255, 255))
        throw sdl_error("Failed to set draw color");
    if (SDL_RenderClear(__sdl_renderer))
        throw sdl_error("Failed to clear render_system");

    // TODO: temp (it just loops over all flipbooks)
    for (auto& entity : __registered_entities) { }
    // Hey this is IMPORTANT!
    SDL_RenderPresent(__sdl_renderer);
}
void render_system::on_animation_event(animation_event& event) { }

} // namespace p201
