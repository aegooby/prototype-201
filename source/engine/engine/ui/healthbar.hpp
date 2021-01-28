
#pragma once
#include "../math.hpp"
#include "../util.hpp"

#include <__common.hpp>

namespace p201
{
namespace ui
{
class healthbar
{
public:
    struct layer
    {
        vector_2 position = vector_2(0.0f, 0.0f);
        float    width    = 0.0f;
        float    height   = 0.0f;
    };
    /** @brief Healthbar "holder". */
    layer background;
    /** @brief Underlying yellow healthbar seen after taking damage. */
    layer damage;
    /** @brief The red healthbar that the player always sees. */
    layer main;
    /** @brief Whether or not to display the healthbar. */
    bool visible = true;

    healthbar();
    ~healthbar() = default;
};
} // namespace ui
} // namespace p201
