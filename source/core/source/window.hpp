

#pragma once
#include <__common.hpp>
#include <input.hpp>
#include <util.hpp>

namespace p201
{

class window
{
protected:
    std::string __title  = std::string();
    bool        __closed = false;

public:
    static constexpr int width  = 1366;
    static constexpr int height = 768;

    keyboard keyboard;
    mouse    mouse;

    handle_types::window* handle = nullptr;

    window(const std::string&);
    ~window();

    void start();
    void stop();

    const std::string& title();
    bool               closed() const;

    void update();

    window(const window&) = delete;
    window(window&&)      = delete;
    window& operator=(const window&) = delete;
    window& operator=(window&&) = delete;
};

} // namespace p201