
#pragma once
#include "__common.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "hitbox.hpp"

namespace p201
{

struct box
{
    float x;
    float y;
    float w;
    float h;

    constexpr box(float x, float y, float w, float h) noexcept
        : x(x), y(y), w(w), h(h)
    {
    }
    ~box() = default;

    constexpr float right() const noexcept
    {
        return x + w;
    }
    constexpr float left() const noexcept
    {
        return x;
    }
    constexpr float bottom() const noexcept
    {
        return y + h;
    }
    constexpr float top() const noexcept
    {
        return y;
    }
    vector_2 center() const noexcept
    {
        return vector_2(x + w / 2.0f, y + h / 2.0f);
    }
    constexpr bool contains(const box& other) const noexcept
    {
        return left() <= other.left() && other.right() <= right() &&
               top() <= other.top() && other.bottom() <= bottom();
    }
    constexpr bool intersects(const box& other) const noexcept
    {
        return !(left() >= other.right() || right() <= other.left() ||
                 top() >= other.bottom() || bottom() <= other.top());
    }
};

inline constexpr bool intersect(const box& one, const box& two) noexcept
{
    return !(one.left() >= two.right() || one.right() <= two.left() ||
             one.top() >= two.bottom() || one.bottom() <= two.top());
}

template<typename type>
class quadtree
{
public:
    struct node
    {
        std::array<std::unique_ptr<node>, 4> children;
        std::vector<type>                    values;

        bool leaf() const
        {
            return !static_cast<bool>(children.at(0));
        }
    };

protected:
    static constexpr size_t threshold   = 16;
    static constexpr size_t max_depth   = 8;
    static constexpr size_t max_objects = 8;

    std::unique_ptr<node> root;

public:
    quadtree()  = default;
    ~quadtree() = default;
};

} // namespace p201
