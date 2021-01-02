
#include "render.hpp"

#include "../__common.hpp"
#include "../entity.hpp"
#include "../entity_manager.hpp"
#include "../event.hpp"
#include "../linalg.hpp"
#include "../quadtree.hpp"
#include "../util.hpp"
#include "../window.hpp"
#include "../world.hpp"

namespace p201
{
namespace systems
{
void render::transform_tile(float x, float y, float w, float h,
                            std::int16_t* vx, std::int16_t* vy)
{
    const vector_3 iso_vec    = iso_matrix * vector_3(x, y, 0.0f);
    const vector_3 iso_vec_p1 = iso_matrix * vector_3(w, 0.0f, 0.0f);
    const vector_3 iso_vec_p2 = iso_matrix * vector_3(w, h, 0.0f);
    const vector_3 iso_vec_p3 = iso_matrix * vector_3(0.0f, h, 0.0f);

    vx[0] = iso_vec.x();
    vy[0] = iso_vec.y();

    vx[1] = iso_vec.x() + iso_vec_p1.x();
    vy[1] = iso_vec.y() + iso_vec_p1.y();

    vx[2] = iso_vec.x() + iso_vec_p2.x();
    vy[2] = iso_vec.y() + iso_vec_p2.y();

    vx[3] = iso_vec.x() + iso_vec_p3.x();
    vy[3] = iso_vec.y() + iso_vec_p3.y();
}
void render::render_grid(SDL_Renderer* renderer, std::size_t size)
{
    std::int16_t vx[4];
    std::int16_t vy[4];
    for (ssize_t x = -1100; x < 1000; x += size)
    {
        for (ssize_t y = 0; y < 2000; y += size)
        {
            transform_tile(x, y, size, size, vx, vy);
            camera_transform(vx, vy);
            polygonRGBA(__sdl_renderer, vx, vy, 4, 200, 200, 200, 255);
        }
    }
}

void render::render_node(const node& node, std::int16_t* vx, std::int16_t* vy)
{
    auto& bounds = node.bounds;
    transform_tile(bounds.x, bounds.y, bounds.w, bounds.h, vx, vy);
    camera_transform(vx, vy);
    polygonRGBA(__sdl_renderer, vx, vy, 4, 0, 200, 0, 255);

    if (!node.leaf)
        for (auto& child : node.children()) render_node(child, vx, vy);
};
void render::render_hitbox(const std::unique_ptr<hitbox>& hitbox)
{
    auto ptr = hitbox.get();
    if (typeid(*ptr) == typeid(hitboxes::circle))
    {
        auto&    circle     = *dynamic_cast<hitboxes::circle*>(ptr);
        vector_3 iso_center = camera_transform(iso_matrix * circle.center);
        ellipseRGBA(__sdl_renderer, iso_center.x(), iso_center.y(),
                    circle.radius, circle.radius / 2.0f, 200, 0, 0, 200);
    }
    if (typeid(*ptr) == typeid(hitboxes::square))
    {
        auto&        square = *dynamic_cast<hitboxes::square*>(ptr);
        std::int16_t vx[4];
        std::int16_t vy[4];

        transform_tile(square.left(), square.top(), square.width, square.height,
                       vx, vy);
        camera_transform(vx, vy);
        polygonRGBA(__sdl_renderer, vx, vy, 4, 200, 0, 0, 255);
    }
}

void render::render_quadtree(const quadtree& quadtree)
{
    std::int16_t vx[4];
    std::int16_t vy[4];
    render_node(quadtree.root, vx, vy);
}

vector_3 render::camera_transform(const vector_3& vector)
{
    const vector_2 shift = world.camera.shift(window::width, window::height);
    return vector_3(vector.x() + shift.x(), vector.y() + shift.y(), vector.z());
}
SDL_FRect render::camera_transform(const SDL_FRect& rect)
{
    const vector_2 shift = world.camera.shift(window::width, window::height);
    SDL_FRect      rect_shift = rect;
    rect_shift.x += shift.x();
    rect_shift.y += shift.y();

    return rect_shift;
}
void render::camera_transform(std::int16_t* vx, std::int16_t* vy)
{
    const vector_2 shift = world.camera.shift(window::width, window::height);
    for (std::size_t i = 0; i < 4; ++i)
    {
        vx[i] += shift.x();
        vy[i] += shift.y();
    }
}

void render::start()
{
    iso_matrix << 1.0f, 1.0f, 0.0f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f;
    iso_matrix /= sqrt_2;
    std::uint32_t flags = global::vsync ? SDL_RENDERER_PRESENTVSYNC : 0;
    __sdl_renderer = SDL_CreateRenderer(world.window.sdl_window(), -1, flags);
    if (!__sdl_renderer) throw sdl_error("Failed to create rendering system");
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

    if (world.keyboard.modifier(modifier::ALT))
    {
        debug(render_quadtree(world.quadtree));
    }

    // Render all the registered entities one by one
    for (auto& id : __registered_entities)
    {
        auto&       entity    = world.entity(id);
        auto&       render    = entity.component<components::render>();
        const auto& transform = entity.component<components::transform>();

        const vector_3 iso_position = iso_matrix * transform.position;

        render.rect.x = iso_position.x() - render.rect.w * render.offset.x();
        render.rect.y = iso_position.y() - render.rect.h * render.offset.y();

        if (entity.flag.test(components::collision::flag) &&
            world.keyboard.modifier(modifier::ALT))
        {
            auto& hitbox = entity.component<components::collision>().hitbox;
            debug(render_hitbox(hitbox));
        }

        if (!render.visible) continue;
        if (!render.texture)
            render.texture = world.sprite_manager.default_sprite(render.family);
        SDL_FRect rect_shift = camera_transform(render.rect);
        render_sprite(render.texture, &rect_shift);
    }

    SDL_RenderPresent(__sdl_renderer);
}

} // namespace systems
} // namespace p201
