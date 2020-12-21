
#pragma once
#include "__common.hpp"

#include <filesystem>
#include <fstream>
#include <vector>
#if defined(P201_POSIX_COMPATIBLE)
#    define P201_DIRECTORY_SLASH '/'
#elif defined(P201_OS_WINDOWS)
#    define P201_DIRECTORY_SLASH '\'
#endif

namespace p201
{

} // namespace p201
