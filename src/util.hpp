
#pragma once
#include "__common.hpp"
#include "linalg.hpp"

#include <chrono>
#include <thread>

namespace p201
{
namespace util
{
inline vector_2 center(const SDL_FRect& rect)
{
    return vector_2(rect.x + rect.w / 2.0f, rect.y + rect.h / 2.0f);
}
inline SDL_FRect rect(const vector_2& center, float width, float height)
{
    SDL_FRect rect = { .w = width, .h = height };

    rect.x = center.x() - width / 2.0f;
    rect.y = center.y() - height / 2.0f;
    return rect;
}
inline void sleep(std::size_t ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
template<int n>
inline std::string to_string(const vector<n>& vector)
{
    std::string str = "(";
    for (std::size_t i = 0; i < n - 1; ++i)
        str += std::to_string(vector[i]) + ", ";
    str += std::to_string(vector[n - 1]) + ")";
    return str;
}
} // namespace util
} // namespace p201

/** @brief Macro to only run a statement in debug mode. */
#if defined(P201_DEBUG)
#    define debug(statement) statement
#else
#    define debug(statement)
#endif
