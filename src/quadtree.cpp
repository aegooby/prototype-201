
#include "quadtree.hpp"

#include "__common.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "world.hpp"

namespace p201
{
quadtree::quadtree(size_t threshold, size_t max_depth, size_t max_objects,
                   size_t width, size_t height, int x, int y)
{
    _threshold   = threshold;
    _max_depth   = max_depth;
    _max_objects = max_objects;
    _width       = width;
    _height      = height;
    _x           = x;
    _y           = y;

    // width,height = 480, 360
};

void quadtree::add_nodes()
{
    nodes[0] =
        std::make_unique<quadtree>(_threshold, _max_depth - 1, _max_objects,
                                   _width / 2, _height / 2, _x + _width, _y);

    nodes[1] =
        std::make_unique<quadtree>(_threshold, _max_depth - 1, _max_objects,
                                   _width / 2, _height / 2, _x, _y);

    nodes[2] =
        std::make_unique<quadtree>(_threshold, _max_depth - 1, _max_objects,
                                   _width / 2, _height / 2, _x, _y - _height);

    nodes[3] = std::make_unique<quadtree>(_threshold, _max_depth - 1,
                                          _max_objects, _width / 2, _height / 2,
                                          _x + _width, _y - _height);
}

void quadtree::populate() { }

void quadtree::smashable() { }

} // namespace p201
