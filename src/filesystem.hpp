
#pragma once
#include "__common.hpp"

#include <fstream>
#include <vector>
#if defined(P201_POSIX_COMPATIBLE)
#    include <dirent.h>
#    include <sys/stat.h>
#    define P201_DIRECTORY_SLASH '/'
#elif defined(P201_OS_WINDOWS)
#    include <windows.h>
#    define P201_DIRECTORY_SLASH '\'
#endif

namespace p201
{

class directory
{
public:
    using dirent = struct dirent;
    using dir    = DIR;
    using file   = FILE;
    enum class mode
    {
        read_only,
        read_write,
    };

protected:
    mode        __mode = mode::read_only;
    std::string __path;
#if defined(P201_POSIX_COMPATIBLE)
    dir*    __directory = nullptr;
    dirent* __entry     = nullptr;
#elif defined(P201_OS_WINDOWS)

#endif
    bool                     __open = false;
    std::vector<std::string> __entries;
    std::vector<std::string> __abs_entries;

public:
    static bool is_directory(const std::string& path)
    {
#if defined(P201_POSIX_COMPATIBLE)
        dir* __ptr = opendir(path.c_str());
        if (__ptr)
        {
            closedir(__ptr);
            return true;
        }
        return false;
#elif defined(P201_OS_WINDOWS)

#endif
    }
    static bool is_file(const std::string& path)
    {
        std::fstream __file(path);
        if (__file.is_open())
        {
            __file.close();
            return true;
        }
        __file.close();
        return false;
    }

public:
    directory() = default;
    directory(mode mode) : __mode(mode) { }
    directory(const std::string& path)
    {
        open(path);
    }
    directory(mode mode, const std::string& path) : __mode(mode)
    {
        open(path);
    }
    ~directory()
    {
        if (__open) close();
    }
    inline __attribute__((always_inline)) bool is_open() const
    {
        return __open;
    }
    __attribute__((always_inline)) const std::string& path() const
    {
        return __path;
    }
    inline __attribute__((always_inline)) const std::vector<std::string>&
    entries() const
    {
        return __entries;
    }
    void create(const std::string& path);
    void open(const std::string& path);
    void close();
    void read();
         operator std::string();
};

} // namespace p201
