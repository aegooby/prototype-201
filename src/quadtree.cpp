
#include "quadtree.hpp"
#include "__common.hpp"
#include "linalg.hpp"

namespace p201
{
<<<<<<< HEAD
quadtree::quadtree(size_t threshold, size_t max_depth, size_t max_objects, size_t width, size_t height, vector_3 position)
=======
quadtree::quadtree(size_t threshold, size_t max_depth, size_t max_objects,
                   size_t width, size_t height, int x, int y)
>>>>>>> 9dc9e8f2a30498a1ee579b46810be78c0f32466f
{
    _threshold   = threshold;
    _max_depth   = max_depth;
    _max_objects = max_objects;
<<<<<<< HEAD
    _width = width;
    _height = height;
    _position = position;
    
// width,height = 480, 360
};

void quadtree::add_nodes() {
    int new_width = _width/2;
    int new_height = _height/2;
    
    nodes[0] = std::make_unique<quadtree>(_threshold, _max_depth-1, _max_objects, new_width, new_height, vector_3(_position(1) + new_width, _position(2), 0));
    
    nodes[1] = std::make_unique<quadtree>(_threshold, _max_depth-1, _max_objects, new_width, new_height, vector_3(_position(1),  _position(2), 0));
    
    nodes[2] = std::make_unique<quadtree>(_threshold, _max_depth-1, _max_objects, new_width, new_height, vector_3(_position(1),  _position(2) - new_height),0);
    
    nodes[3] = std::make_unique<quadtree>(_threshold, _max_depth-1, _max_objects, new_width, new_height, vector_3(_position(1) + new_width, _position(2) - new_height,0));
}
=======
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
>>>>>>> 9dc9e8f2a30498a1ee579b46810be78c0f32466f

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
