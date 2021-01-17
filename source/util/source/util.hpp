
#pragma once
#include "linalg.hpp"

#include <__common.hpp>
#include <chrono>
#include <physx.hpp>
#include <thread>

namespace p201
{
namespace util
{

vector_2  center(const SDL_FRect& rect);
SDL_FRect rect(const vector_2& center, float width, float height);

void sleep(std::size_t ms);

std::string to_string(const px::vector_3& vector);
std::string to_string(const px::vector_3ext& vector);
std::string to_string(std::thread::id id);

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
