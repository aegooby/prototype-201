
#pragma once
#include "input_enum.hpp"

#include <__common.hpp>
#include <array>
#include <util.hpp>

namespace p201
{

/**
 * @brief These macros were defined in another file for the sake of conserving
 *        space in this file since they are very long.
 * @see input_enum.hpp
 */
KEY_ENUM();
MODIFIER_ENUM();
MOUSE_ENUM();

template<std::size_t size, typename... types>
bool multi_test(const std::array<bool, size>& array, types... args)
{
    bool result = true;
    for (auto& code : { args... })
        result = result && array.at(std::size_t(code));
    return result;
}
template<std::size_t size, typename... types>
void multi_set(std::array<bool, size>& array, bool value, types... args)
{
    for (auto& code : { args... }) array.at(std::size_t(code)) = value;
}

class input
{
protected:
    window& window_context;

public:
    input(window& window_context) : window_context(window_context) { }
    ~input() = default;

    input(const input&) = delete;
    input(input&&)      = delete;
    input& operator=(const input&) = delete;
    input& operator=(input&&) = delete;
};

class keyboard : public input
{
protected:
    std::array<bool, std::size_t(keycode::size)>  __scan;
    std::array<bool, std::size_t(keycode::size)>  __down;
    std::array<bool, std::size_t(keycode::size)>  __up;
    std::array<bool, std::size_t(modifier::size)> __modifier;

public:
    keyboard(window& window_context) : input(window_context)
    {
        __scan.fill(false);
        __down.fill(false);
        __up.fill(false);
    }
    ~keyboard()
    {
        __scan.fill(false);
        __down.fill(false);
        __up.fill(false);
    }
    template<typename... types>
    bool scan(types... args) const
    {
        return multi_test(__scan, args...);
    }
    template<typename... types>
    bool down(types... args) const
    {
        return multi_test(__down, args...);
    }
    template<typename... types>
    bool up(types... args) const
    {
        return multi_test(__up, args...);
    }
    template<typename... types>
    void scan_set(bool value, types... args)
    {
        multi_set(__scan, value, args...);
    }
    template<typename... types>
    void down_set(bool value, types... args)
    {
        multi_set(__down, value, args...);
    }
    template<typename... types>
    void up_set(bool value, types... args)
    {
        multi_set(__up, value, args...);
    }
    void scan_clear()
    {
        __scan.fill(false);
    }
    void down_clear()
    {
        __down.fill(false);
    }
    void up_clear()
    {
        __up.fill(false);
    }
    template<typename... types>
    bool modifier(types... args) const
    {
        return multi_test(__modifier, args...);
    }
    template<typename... types>
    void modifier_set(bool value, types... args)
    {
        multi_set(__modifier, value, args...);
    }
    void update()
    {
        auto __mod = SDL_GetModState();
        modifier_set(bool(__mod & KMOD_ALT), modifier::ALT);
        modifier_set(bool(__mod & KMOD_CTRL), modifier::CTRL);
        modifier_set(bool(__mod & KMOD_GUI), modifier::GUI);
        modifier_set(bool(__mod & KMOD_SHIFT), modifier::SHIFT);
        modifier_set(bool(__mod == KMOD_NONE), modifier::NONE);
    }

    keyboard(const keyboard&) = delete;
    keyboard(keyboard&&)      = delete;
    keyboard& operator=(const keyboard&) = delete;
    keyboard& operator=(keyboard&&) = delete;
};

class mouse : public input
{
protected:
    /** @brief Keycode state storages. */
    std::array<bool, std::size_t(mousecode::size)> __scan;
    std::array<bool, std::size_t(mousecode::size)> __down;
    std::array<bool, std::size_t(mousecode::size)> __up;
    /** @brief Movement and position of mouse on screen. */
    vector_2 __position;
    vector_2 __movement;

public:
    mouse(window& window_context) : input(window_context)
    {
        __scan.fill(false);
        __down.fill(false);
        __up.fill(false);
    }
    ~mouse()
    {
        __scan.fill(false);
        __down.fill(false);
        __up.fill(false);
    }
    template<typename... types>
    bool scan(types... args) const
    {
        return multi_test(__scan, args...);
    }
    template<typename... types>
    bool down(types... args) const
    {
        return multi_test(__down, args...);
    }
    template<typename... types>
    bool up(types... args) const
    {
        return multi_test(__up, args...);
    }
    template<typename... types>
    void scan_set(bool value, types... args)
    {
        multi_set(__scan, value, args...);
    }
    template<typename... types>
    void down_set(bool value, types... args)
    {
        multi_set(__down, value, args...);
    }
    template<typename... types>
    void up_set(bool value, types... args)
    {
        multi_set(__up, value, args...);
    }
    void scan_clear()
    {
        __scan.fill(false);
    }
    void down_clear()
    {
        __down.fill(false);
    }
    void up_clear()
    {
        __up.fill(false);
    }
    void visible(bool visible)
    {
        SDL_ShowCursor(int(visible));
    }
    const vector_2& position() const
    {
        return __position;
    }
    const vector_2& movement() const
    {
        return __movement;
    }
    bool visible() const
    {
        return SDL_ShowCursor(-1);
    }
    void position(float x, float y);
    void position(const vector_2&);
    void update()
    {
        int x, y;
        int dx, dy;
        SDL_GetMouseState(&x, &y);
        SDL_GetRelativeMouseState(&dx, &dy);
        __position.x() = float(x);
        __position.y() = float(y);
        __movement.x() = float(dx);
        __movement.y() = float(dy);
    }

    mouse(const mouse&) = delete;
    mouse(mouse&&)      = delete;
    mouse& operator=(const mouse&) = delete;
    mouse& operator=(mouse&&) = delete;
};

} // namespace p201
