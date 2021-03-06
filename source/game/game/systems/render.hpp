
#pragma once
#include "../camera.hpp"
#include "../components.hpp"

#include <engine/__common.hpp>
#include <engine/core.hpp>
#include <engine/ecs.hpp>
#include <engine/event.hpp>
#include <engine/util.hpp>
#include <unordered_map>

/* clang-format off */
/** @note This is stored in column-major order */
static constexpr float __iso_mat_array[6] = 
{ 
    /* Column 1 */
    1.0f, 
    -0.5f, 
    
    /* Column 2 */
    1.0f, 
    0.5f, 
    
    /* Column 3 */
    0.0f, 
    -1.0f 
};
/* clang-format on */

namespace p201
{
namespace systems
{
class render : public system
{
public:
    using __base = system;

protected:
    const matrix_32 iso_mat = glm::make_mat3x2(__iso_mat_array) / forge::sqrt_2;
    /** @brief How many times do I have to tell you to read the name retard? */
    camera camera;

private:
    void render_sprite(SDL_Texture*, SDL_Rect*, SDL_FRect*);

public:
    render(class world& world) : __base(world)
    {
        flag.set(components::render::flag);
        flag.set(components::transform::flag);
    }
    virtual ~render() override
    {
        stop();
    }

    virtual void start() override;
    void         stop();
    virtual void update(float dt) override;
    void         draw(float alpha);
    void         display();

    render(const render&) = delete;
    render(render&&)      = delete;
    render& operator=(const render&) = delete;
    render& operator=(render&&) = delete;
};
} // namespace systems
} // namespace p201
