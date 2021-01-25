
#pragma once
#include "../physx.hpp"
#include "linalg.hpp"
#include "../media-layer.hpp"

#include <__common.hpp>
#include <chrono>
#include <thread>

namespace p201
{
namespace util
{

vector_2  center(const SDL_FRect& rect);
SDL_FRect rect(const vector_2& center, float width, float height);

void sleep(std::size_t ms);

std::string to_string(const px::vector_3&);
std::string to_string(const px::vector_3ext&);
std::string to_string(std::thread::id);
std::string to_string(const vector_2&);
std::string to_string(const vector_3&);
} // namespace util
} // namespace p201
