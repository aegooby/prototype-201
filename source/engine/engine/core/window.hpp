

#pragma once
#include "../input.hpp"
#include "../util.hpp"

#include <__common.hpp>

namespace p201
{

class window
{
protected:
    bool __closed = false;

public:
    static constexpr int width  = 1366;
    static constexpr int height = 768;

    std::string title = std::string();

    keyboard keyboard;
    mouse    mouse;

    handle_types::window* handle = nullptr;

    window(const std::string&);
    ~window();

    void start();
    void stop();

    bool closed() const;

    void update();

    window(const window&) = delete;
    window(window&&)      = delete;
    window& operator=(const window&) = delete;
    window& operator=(window&&) = delete;
};

} // namespace p201