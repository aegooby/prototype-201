
#pragma once
#include "../math.hpp"
#include "../physx.hpp"

#include <__common.hpp>
#include <chrono>
#include <thread>

namespace p201
{
namespace util
{

void sleep(std::size_t ms);

std::string to_string(const px::vector_3&);
std::string to_string(const px::vector_3ext&);
std::string to_string(std::thread::id);
std::string to_string(const vector_2&);
std::string to_string(const vector_3&);
} // namespace util
} // namespace p201
