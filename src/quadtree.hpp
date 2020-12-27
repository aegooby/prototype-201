
#pragma once
#include "__common.hpp"
#include "linalg.hpp"

#include <unordered_map>


namespace p201
{

class quadtree
{
private:
    std::size_t                _threshold;
    std::size_t                _max_depth;
    std::size_t                _max_objects;
    std::size_t                _width;
    std::size_t                _height;
    vector_3              _position; //top left x & y pos
    
    std::unique_ptr<quadtree> nodes [4];

public:
    quadtree(std::size_t threshold, std::size_t max_depth, std::size_t max_objects, std::size_t width, std::size_t height, vector_3 position);
    ~quadtree() = default;
    void add_nodes();
    void populate(std::unordered_map<id_t, std::reference_wrapper<entity>> entities);
    void get_entities(vector_3 position, std::unordered_map<id_t, std::reference_wrapper<entity>> entities);
    
};

} // namespace p201
