
#include "render_system.hpp"

#include "__common.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "event.hpp"
#include "filesystem.hpp"
#include "state.hpp"
#include "world.hpp"

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
    //    render.add_flipbook
}

void render_system::load(const std::string& path)
{
    std::string __path = path;
    if (__path.back() != TD_DIRECTORY_SLASH) __path += TD_DIRECTORY_SLASH;
    //    for (auto& entity_type : flipbooks)
    //    {
    //        auto&    type = entity_type.first;
    //        textures.emplace(type, IMG_LoadTexture(__sdl_renderer, (__path +
    //        spritesheet_names.at(type) + ".png").c_str())); if
    //        (!textures.at(type))
    //            throw sdl_error("Failed to load texture");
    //    }
    //    for (auto& entity : __registered_entities)
    //    {
    //        auto&    render =
    //        entity.second.get().component<render_component>(); auto&    type =
    //        entity.second.get().type; for (auto& flipbook :
    //        flipbooks.at(type))
    //        {
    //            load_flipbook(render, flipbook.first, 20.0f, flipbook.second);
    //        }
    //    }
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
    render_sprite(textures.at(entity.type), rect,
                  flipbook.info.origin +
                      point_2(rect->w * flipbook.index, 0.0f));
    ++flipbook.framec %= flipbook.frame_delay();
    if (!flipbook.framec) ++flipbook.index %= flipbook.frames();
    if (!flipbook.index &&
        flipbook.frames() > 1 /* add exception for idle state? */)
    {
        //        world.event_bus.publish<animation_complete_event>(entity,
        //        flipbook.name());
    }
}

void render_system::render()
{
    if (SDL_SetRenderDrawColor(__sdl_renderer, 0, 0, 255, 255))
        throw sdl_error("Failed to set draw color");
    if (SDL_RenderClear(__sdl_renderer))
        throw sdl_error("Failed to clear render_system");

    // TODO: temp (it just renders all flipbooks)
    for (auto& entity : __registered_entities)
    {
        auto& render    = entity.second.get().component<render_component>();
        auto& transform = entity.second.get().component<transform_component>();
        //        auto&    state =
        //        entity.second.get().component<state_component>();
        render.rect.x = transform.position.x;
        render.rect.y = transform.position.y;
        //        render.rect.w = render.flipbooks.at(state.state).info.width;
        //        render.rect.h = render.flipbooks.at(state.state).info.height;
        //        render_flipbook(entity.second.get(),
        //        render.flipbooks.at(state.state), &(render.rect));
    }
    // Hey this is IMPORTANT!
    SDL_RenderPresent(__sdl_renderer);
}
void render_system::on_animation_event(animation_event& event)
{
    //    event.entity.component<render_component>().name = event.name;
}

} // namespace p201
