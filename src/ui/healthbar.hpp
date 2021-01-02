
#pragma once
#include "../__common.hpp"
#include "../linalg.hpp"

namespace p201
{
namespace ui
{
class healthbar
{
public:
    struct layer
    {
        SDL_Texture* texture  = nullptr;
        SDL_FRect    rect     = { .x = 0.0f, .y = 0.0f, .w = 0.0f, .h = 0.0f };
        SDL_Rect     srcrect  = { .x = 0, .y = 0, .w = 0, .h = 0 };
        vector_2     position = vector_2(0.0f, 0.0f);
        float        width    = 0.0f;
        float        height   = 0.0f;
    };
    /** @brief Healthbar "holder". */
    layer background;
    /** @brief Underlying yellow healthbar seen after taking damage. */
    layer damage;
    /** @brief The red healthbar that the player always sees. */
    layer main;
    /** @brief Whether or not to display the healthbar. */
    bool visible = true;

    healthbar()  = default;
    ~healthbar() = default;
};
} // namespace ui
} // namespace p201
