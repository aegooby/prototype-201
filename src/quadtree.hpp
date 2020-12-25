
#pragma once
#include "__common.hpp"
#include "linalg.hpp"

namespace p201
{

class quadtree
{
private:
    size_t                _threshold;
    size_t                _max_depth;
    size_t                _max_objects;
    size_t                _width;
    size_t                _height;
    vector_3              _position; //top left x & y pos
    
    std::unique_ptr<quadtree> nodes [4];

public:
    quadtree(size_t threshold, size_t max_depth, size_t max_objects, size_t width, size_t height, vector_3 position);
    ~quadtree() = default;
    void add_nodes();
    void populate();
    void smashable();
};

} // namespace p201
