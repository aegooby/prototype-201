
#include "filesystem.hpp"

#include "__common.hpp"

namespace p201
{

__attribute__((always_inline)) void directory::create(const std::string& path)
{
#if defined(TD_POSIX_COMPATIBLE)
    mkdir(path.c_str(), ACCESSPERMS);
#elif defined(TD_OS_WINDOWS)
#endif
}
__attribute__((always_inline)) void directory::open(const std::string& path)
{
    __path = path;
    if (__path.back() != TD_DIRECTORY_SLASH) __path += TD_DIRECTORY_SLASH;
    if (is_file(path))
        throw std::runtime_error(
            std::string("Attempt to open a file as a directory: ") + __path);
    if (is_directory(path))
    {
#if defined(TD_POSIX_COMPATIBLE)
        __directory = opendir(path.c_str());
#elif defined(TD_OS_WINDOWS)
#endif
    }
    else
    {
        switch (__mode)
        {
            case mode::read_only:
                throw std::runtime_error(std::string("Directory not found: ") +
                                         path);
                break;
            case mode::read_write:
                create(path);
                break;
        }
    }
    __open = true;
}
__attribute__((always_inline)) void directory::close()
{
#if defined(TD_POSIX_COMPATIBLE)
    closedir(__directory);
    __directory = nullptr;
    __entry     = nullptr;
#elif defined(TD_OS_WINDOWS)
#endif
    __open = false;
    __path = std::string();
}
__attribute__((always_inline)) void directory::read()
{
#if defined(TD_POSIX_COMPATIBLE)
    rewinddir(__directory);
    while ((__entry = readdir(__directory)))
    {
        if (std::string(__entry->d_name) != "." &&
            std::string(__entry->d_name) != "..")
        { __entries.emplace_back(__entry->d_name); }
    }
#elif defined(TD_OS_WINDOWS)
#endif
}
__attribute__((always_inline)) directory::operator std::string()
{
    return path();
}

} // namespace p201
