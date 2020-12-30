
#pragma once
#include "__common.hpp"
#include "entity.hpp"
#include "linalg.hpp"

#include <array>
#include <functional>
#include <span>
#include <unordered_map>

namespace p201
{

class bounding_box
{
private:
    const float __x, __y, __w, __h;

public:
    bounding_box(float x, float y, float w, float h)
        : __x(x), __y(y), __w(w), __h(h)
    {
    }
    ~bounding_box() = default;

    float left() const
    {
        return __x;
    }
    float right() const
    {
        return __x + __w;
    }
    float top() const
    {
        return __y;
    }
    float bottom() const
    {
        return __y + __h;
    }
};

struct node
{
    /**
     * @brief Index of the first child if the node is a branch,
     *        or the first entity if the node is a leaf.
     */
    std::size_t index;
    /** @brief Will be -1 if the node is not a leaf. */
    std::int8_t count;
    /** @brief Bounds for the node. */
    bounding_box bounds;

    node(std::size_t index, std::int8_t count, bounding_box bounds)
        : index(index), count(count), bounds(bounds)
    {
    }
    ~node() = default;

    bool leaf() const
    {
        return index > -1;
    }
    std::span<node, 4> children(std::vector<node>& nodes)
    {
        if (leaf()) throw std::runtime_error("Node is a leaf");
        return std::span(nodes.data() + index, 4);
    }
    std::span<std::size_t, 4> entities(std::vector<std::size_t>& entities)
    {
        if (!leaf()) throw std::runtime_error("Node is not a leaf");
        return std::span(entities.data() + index, 4);
    }
};

class quadtree
{
protected:
    std::vector<node> __nodes;
    /** @brief Entities stored by id. */
    std::vector<std::size_t> __entities;
    /** @brief Maximum number of subdivisions. */
    std::size_t max_depth;
    /** @brief Maximum number of objects that can be stored in a node. */
    std::size_t threshold;

private:
    void split(std::size_t node_index)
    {
        auto entities = __nodes.at(node_index).entities(__entities);
        __nodes.at(node_index).index = __nodes.size();
        for (auto& entity : entities) { nodes.emplace_back() }
        // nodes.emplace_back(node(..., -1))
    }
    void insert(std::size_t);

public:
    quadtree(std::size_t max_depth, std::size_t threshold,
             const vector_2& origin, float width, float height)
        : max_depth(max_depth),
          threshold(threshold),
          origin(origin),
          width(width),
          height(height)
    {
    }
    ~quadtree() = default;

    void  update();
    node& root()
    {
        return __nodes.at(0);
    }
    const node& root() const
    {
        return __nodes.at(0);
    }
};

} // namespace p201
