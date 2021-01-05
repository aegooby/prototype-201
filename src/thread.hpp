
#pragma once
#include "__common.hpp"
#include "util.hpp"

#include <future>
#include <thread>

namespace p201
{
namespace thread
{
inline std::string id()
{
    return util::to_string(std::this_thread::get_id());
}
} // namespace thread
} // namespace p201
