
#pragma once
#include "__common.hpp"
#include "entity.hpp"
#include "linalg.hpp"

#include <array>
#include <list>
#include <unordered_set>
#include <variant>

namespace p201
{

class box
{
public:
    float x = 0.0f, y = 0.0f, w = 0.0f, h = 0.0f;

    box() = default;
    box(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) { }
    ~box() = default;
    
    box top_left() const
    {
        return box(x, y, w / 2.0f, h / 2.0f);
    }
    box top_right() const
    {
        return box(x + w / 2.0f, y, w / 2.0f, h / 2.0f);
    }
    box bottom_left() const
    {
        return box(x, y + h / 2.0f, w / 2.0f, h / 2.0f);
    }
    box bottom_right() const
    {
        return box(x + w / 2.0f, y + h / 2.0f, w / 2.0f, h / 2.0f);
    }
};

struct node
{
    using children_t      = std::array<node, 4>;
    using entities_t      = std::vector<std::size_t>;
    using children_list_t = std::list<children_t>;
    using entities_list_t = std::list<entities_t>;

    std::variant<children_list_t::iterator, entities_list_t::iterator> data;

    bool leaf = true;
    box  bounds;

    node()  = default;
    ~node() = default;

    std::size_t count() const
    {
        if (!leaf)
        {
            std::size_t total = 0;
            for (const auto& child : children()) total += child.count();
            return total;
        }
        return entities().size();
    }
    children_list_t::iterator& children_iter()
    {
        if (leaf) throw std::runtime_error("Called children() on leaf");
        return std::get<children_list_t::iterator>(data);
    }
    entities_list_t::iterator& entities_iter()
    {
        if (!leaf) throw std::runtime_error("Called entities() on non-leaf");
        return std::get<entities_list_t::iterator>(data);
    }
    const children_list_t::iterator& children_iter() const
    {
        if (leaf) throw std::runtime_error("Called children() on leaf");
        return std::get<children_list_t::iterator>(data);
    }
    const entities_list_t::iterator& entities_iter() const
    {
        if (!leaf) throw std::runtime_error("Called entities() on non-leaf");
        return std::get<entities_list_t::iterator>(data);
    }
    std::array<node, 4>& children()
    {
        if (leaf) throw std::runtime_error("Called children() on leaf");
        return *children_iter();
    }
    std::vector<std::size_t>& entities()
    {
        if (!leaf) throw std::runtime_error("Called entities() on non-leaf");
        return *entities_iter();
    }
    const std::array<node, 4>& children() const
    {
        if (leaf) throw std::runtime_error("Called children() on leaf");
        return *children_iter();
    }
    const std::vector<std::size_t>& entities() const
    {
        if (!leaf) throw std::runtime_error("Called entities() on non-leaf");
        return *entities_iter();
    }
};

class quadtree
{
protected:
    class world& world;
    /** @brief The first node (index 0) is always the root. */
    std::list<std::array<node, 4>> __nodes;
    /** @brief Entities stored by id. */
    std::list<std::vector<std::size_t>> __entities;
    /** @brief Maximum number of subdivisions. */
    std::size_t max_depth = 0;
    /** @brief Maximum number of objects that can be stored in a node. */
    std::size_t threshold;

private:
    bool is_in(std::size_t, const box&);
    void insert(std::size_t, node&, std::size_t);
    void remove(std::size_t, node&);
    void leaves(node& node, std::list<std::vector<std::size_t>>&);

public:
    node root;

    quadtree(class world& world) : world(world) { }
    ~quadtree() = default;

    void start(std::size_t max_depth, std::size_t threshold, const box& bounds)
    {
        this->max_depth = max_depth;
        this->threshold = threshold;
        root.bounds     = bounds;
        __entities.emplace_back();
        root.data = --__entities.end();
    }
    void split(node& node);
    void insert(std::size_t);
    void remove(std::size_t);
    void insert(std::unordered_set<std::size_t>&);
    void remove(std::unordered_set<std::size_t>&);
    std::list<std::vector<std::size_t>> leaves();
};

} // namespace p201
