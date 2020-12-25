
#pragma once
#include "__common.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "world.hpp"

namespace p201
{

class quadtree
{
private:
    size_t _threshold;
    size_t _max_depth;
    size_t _max_objects;
    size_t _width;
    size_t _height;
    int    _x; // top left x position
    int    _y; // top left y position

    std::unique_ptr<quadtree> nodes[4];

public:
    quadtree(size_t threshold, size_t max_depth, size_t max_objects,
             size_t width, size_t height, int x, int y);
    ~quadtree() = default;
    void add_nodes();
    void populate();
    void smashable();
};

} // namespace p201
