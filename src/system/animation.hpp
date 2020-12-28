
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
    class animation : public system
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
        animation(class world& world)
            : __base(world), sprite_manager(__sdl_renderer)
        {
            flag.set(component::flag::render);
            flag.set(component::flag::animation);
        }
        virtual ~animation() = default;
        virtual void start() override;
        virtual void update() override;

        //	Preventing copying and moving
        animation(const animation&) = delete;
        animation(animation&&)      = delete;
        animation& operator=(const animation&) = delete;
        animation& operator=(animation&&) = delete;
    };
} // namespace systems
} // namespace p201
