
#pragma once
#include "__common.hpp"
#include "linalg.hpp"
#include "util.hpp"
#include "window.hpp"

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
    vector_3 transform(const vector_3& vector)
    {
        const vector_2 shift = this->shift(window::width, window::height);
        return vector_3(vector.x() + shift.x(), vector.y() + shift.y(),
                        vector.z());
    }
    SDL_FRect transform(const SDL_FRect& rect)
    {
        const vector_2 shift      = this->shift(window::width, window::height);
        SDL_FRect      rect_shift = rect;
        rect_shift.x += shift.x();
        rect_shift.y += shift.y();

        return rect_shift;
    }
    void transform(std::int16_t* vx, std::int16_t* vy)
    {
        const vector_2 shift = this->shift(window::width, window::height);
        for (std::size_t i = 0; i < 4; ++i)
        {
            vx[i] += shift.x();
            vy[i] += shift.y();
        }
    }
};
} // namespace p201
