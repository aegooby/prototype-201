

#pragma once
#include <__common.hpp>
#include <input.hpp>
#include <util.hpp>

namespace p201
{

class window
{
protected:
    std::string   __title      = std::string();
    SDL_Window*   __sdl_window = nullptr;
    bool          __closed     = false;
    SDL_SysWMinfo __syswm_info = SDL_SysWMinfo();

public:
    static constexpr int width  = 1366;
    static constexpr int height = 768;

    keyboard keyboard;
    mouse    mouse;
    window(const std::string&);
    ~window();

    void start();
    void stop();

    const std::string&   title();
    SDL_Window*          sdl_window();
    bool                 closed() const;
    const SDL_SysWMinfo& syswm_info() const;

    void update();

    window(const window&) = delete;
    window(window&&)      = delete;
    window& operator=(const window&) = delete;
    window& operator=(window&&) = delete;
};

} // namespace p201