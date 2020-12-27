
#pragma once
#include "../__common.hpp"
#include "../entity.hpp"
#include "../exception.hpp"
#include "../sprite.hpp"
#include "../window.hpp"
#include "system.hpp"

#include <unordered_map>

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
        matrix_3        iso_matrix;
        sprite::manager sprite_manager;

        void render_sprite(SDL_Texture*, SDL_FRect*);
        void render_flipbook(sprite::flipbook&, SDL_FRect*);
        void render_grid(SDL_Renderer*, std::size_t, std::uint8_t);
        void iso_tile(const vector_3&, SDL_FRect&, std::int16_t*,
                      std::int16_t*);

    public:
        render(class world& world)
            : __base(world), sprite_manager(__sdl_renderer)
        {
            flag.set(component::flag::render);
            flag.set(component::flag::transform);
        }
        virtual ~render()
        {
            stop();
        }
        virtual void  start() override;
        void          start(class window&);
        void          load();
        void          stop();
        SDL_Renderer* sdl_renderer()
        {
            return __sdl_renderer;
        }
        virtual void update() override { }
        void         render_frame();

        //	Preventing copying and moving
        render(const render&) = delete;
        render(render&&)      = delete;
        render& operator=(const render&) = delete;
        render& operator=(render&&) = delete;
    };
} // namespace systems
} // namespace p201
