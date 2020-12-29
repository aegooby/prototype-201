
#pragma once
#include "__common.hpp"
#include "linalg.hpp"
#include "util.hpp"

namespace p201
{
class camera
{
public:
    bool     active   = false;
    vector_2 center   = vector_2(0.0f, 0.0f);
    vector_2 velocity = vector_2(0.0f, 0.0f);

    camera()  = default;
    ~camera() = default;
    vector_2 shift(float window_width, float window_height)
    {
        return vector_2(window_width / 2.0f, window_height / 2.0f) - center;
    }
};
} // namespace p201
