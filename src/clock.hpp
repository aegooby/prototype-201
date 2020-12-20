
#pragma once
#include "__common.hpp"

#include <chrono>
#include <ctime>

namespace p201
{

using t_point = std::chrono::high_resolution_clock::time_point;
using nanosec = std::chrono::nanoseconds;

template<typename duration_type>
inline __attribute__((always_inline)) auto nano_cast(duration_type duration)
{
    return std::chrono::duration_cast<nanosec>(duration);
}

static constexpr double nsps  = 1.0E9;
static constexpr double nspms = 1.0E6;

class clock
{
    protected:
    inline static t_point start = std::chrono::high_resolution_clock::now();
    inline static t_point now()
    {
        return std::chrono::high_resolution_clock::now();
    }

    public:
    clock()  = default;
    ~clock() = default;
    inline void reset()
    {
        start = std::chrono::high_resolution_clock::now();
    }
    inline double time_s()
    {
        return nano_cast(now() - start).count() / nsps;
    }
    inline double time_ms()
    {
        return nano_cast(now() - start).count() / nspms;
    }
    inline std::string date_time() const
    {
        std::time_t time = std::time(0);
        std::tm*    date = std::localtime(&time);
        return (std::to_string(date->tm_mday) + "/" +
                std::to_string(date->tm_mon + 1) + "/" +
                std::to_string(date->tm_year + 1900) + ", " +
                std::to_string(date->tm_hour) + ":" +
                std::to_string(date->tm_min) + ":" +
                std::to_string(date->tm_sec) + " UTC");
    }

    //	Preventing copying and moving
    clock(const clock&) = delete;
    clock(clock&&)      = delete;
    clock& operator=(const clock&) = delete;
    clock& operator=(clock&&) = delete;
};

} // namespace p201
