
#include "__common.hpp"
#include "util.hpp"

#include <future>
#include <tbb/concurrent_hash_map.h>
#include <thread>

namespace p201
{
namespace thread
{
inline std::string this_id()
{
    return util::to_string(std::this_thread::get_id());
}
} // namespace thread
} // namespace p201
