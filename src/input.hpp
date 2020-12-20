
#pragma once
#include "__common.hpp"
#include "array.hpp"
#include "key.hpp"
#include "vector.hpp"

namespace p201
{

class input
{
    protected:
    window& window_context;

    public:
    input(window& window_context) : window_context(window_context) { }
    ~input() = default;

    //	Preventing copying and moving
    input(const input&) = delete;
    input(input&&)      = delete;
    input& operator=(const input&) = delete;
    input& operator=(input&&) = delete;
};

class keyboard : public input
{
    protected:
    array<bool, size_t(keycode::size)>  __scan;
    array<bool, size_t(keycode::size)>  __down;
    array<bool, size_t(keycode::size)>  __up;
    array<bool, size_t(modifier::size)> __modifier;

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
    inline __attribute__((always_inline)) bool scan(keycode code) const
    {
        return __scan.at(size_t(code));
    }
    inline __attribute__((always_inline)) bool down(keycode code) const
    {
        return __down.at(size_t(code));
    }
    inline __attribute__((always_inline)) bool up(keycode code) const
    {
        return __up.at(size_t(code));
    }
    inline __attribute__((always_inline)) bool
    scan(const std::unique_ptr<key>& code) const
    {
        auto ptr = code.get();
        if (typeid(*ptr) == typeid(single_key))
        { return scan(static_cast<single_key*>(ptr)->code); }
        else if (typeid(*ptr) == typeid(multi_key))
        {
            for (auto& key : static_cast<multi_key*>(ptr)->codes)
            {
                if (!scan(key)) return false;
            }
            return true;
        }
        else
            throw std::runtime_error("Invalid typeid");
    }
    inline __attribute__((always_inline)) bool
    down(const std::unique_ptr<key>& code) const
    {
        auto ptr = code.get();
        if (typeid(*ptr) == typeid(single_key))
        { return down(static_cast<single_key*>(ptr)->code); }
        else if (typeid(*ptr) == typeid(multi_key))
        {
            size_t scan_count = 0, down_count = 0,
                   size = static_cast<multi_key*>(ptr)->codes.size();
            for (auto& key : static_cast<multi_key*>(ptr)->codes)
            {
                if (scan(key) && !down(key)) ++scan_count;
                if (down(key)) ++down_count;
            }
            return (scan_count + down_count == size && scan_count < size);
        }
        else
            throw std::runtime_error("Invalid typeid");
    }
    inline __attribute__((always_inline)) bool
    up(const std::unique_ptr<key>& code) const
    {
        auto ptr = code.get();
        if (typeid(*ptr) == typeid(single_key))
        { return up(static_cast<single_key*>(ptr)->code); }
        else if (typeid(*ptr) == typeid(multi_key))
        {
            size_t scan_count = 0, up_count = 0,
                   size = static_cast<multi_key*>(ptr)->codes.size();
            for (auto& key : static_cast<multi_key*>(ptr)->codes)
            {
                if (scan(key)) ++scan_count;
                if (up(key)) ++up_count;
            }
            return (scan_count + up_count == size && scan_count < size);
        }
        else
            throw std::runtime_error("Invalid typeid");
    }
    inline __attribute__((always_inline)) void scan(keycode code, bool value)
    {
        __scan.at(size_t(code)) = value;
    }
    inline __attribute__((always_inline)) void down(keycode code, bool value)
    {
        __down.at(size_t(code)) = value;
    }
    inline __attribute__((always_inline)) void up(keycode code, bool value)
    {
        __up.at(size_t(code)) = value;
    }
    inline __attribute__((always_inline)) void scan_clear()
    {
        __scan.fill(false);
    }
    inline __attribute__((always_inline)) void down_clear()
    {
        __down.fill(false);
    }
    inline __attribute__((always_inline)) void up_clear()
    {
        __up.fill(false);
    }
    inline __attribute__((always_inline)) bool
    modifier(enum modifier code) const
    {
        return __modifier.at(size_t(code));
    }
    inline __attribute__((always_inline)) void modifier(enum modifier code,
                                                        bool          value)
    {
        __modifier.at(size_t(code)) = value;
    }
    inline __attribute__((always_inline)) void update()
    {
        auto __mod = SDL_GetModState();
        modifier(modifier::ALT, bool(__mod & KMOD_ALT));
        modifier(modifier::CTRL, bool(__mod & KMOD_CTRL));
        modifier(modifier::GUI, bool(__mod & KMOD_GUI));
        modifier(modifier::SHIFT, bool(__mod & KMOD_SHIFT));
        modifier(modifier::NONE, bool(__mod == KMOD_NONE));
    }

    //	Preventing copying and moving
    keyboard(const keyboard&) = delete;
    keyboard(keyboard&&)      = delete;
    keyboard& operator=(const keyboard&) = delete;
    keyboard& operator=(keyboard&&) = delete;
};

class mouse : public input
{
    protected:
    array<bool, size_t(mousecode::size)> __scan;
    array<bool, size_t(mousecode::size)> __down;
    array<bool, size_t(mousecode::size)> __up;
    vector_2                             __position;
    vector_2                             __movement;

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
    inline __attribute__((always_inline)) bool scan(mousecode code) const
    {
        return __scan.at(size_t(code));
    }
    inline __attribute__((always_inline)) bool down(mousecode code) const
    {
        return __down.at(size_t(code));
    }
    inline __attribute__((always_inline)) bool up(mousecode code) const
    {
        return __up.at(size_t(code));
    }
    inline __attribute__((always_inline)) void scan(mousecode code, bool value)
    {
        __scan.at(size_t(code)) = value;
    }
    inline __attribute__((always_inline)) void down(mousecode code, bool value)
    {
        __down.at(size_t(code)) = value;
    }
    inline __attribute__((always_inline)) void up(mousecode code, bool value)
    {
        __up.at(size_t(code)) = value;
    }
    inline __attribute__((always_inline)) void scan_clear()
    {
        __scan.fill(false);
    }
    inline __attribute__((always_inline)) void down_clear()
    {
        __down.fill(false);
    }
    inline __attribute__((always_inline)) void up_clear()
    {
        __up.fill(false);
    }
    inline __attribute__((always_inline)) void visible(bool visible)
    {
        SDL_ShowCursor(int(visible));
    }
    inline __attribute__((always_inline)) vector_2 position() const
    {
        return __position;
    }
    inline __attribute__((always_inline)) vector_2 movement() const
    {
        return __movement;
    }
    inline __attribute__((always_inline)) bool visible() const
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
        __position.x = float(x);
        __position.y = float(y);
        __movement.x = float(dx);
        __movement.y = float(dy);
    }

    //	Preventing copying and moving
    mouse(const mouse&) = delete;
    mouse(mouse&&)      = delete;
    mouse& operator=(const mouse&) = delete;
    mouse& operator=(mouse&&) = delete;
};

} // namespace p201
