
#pragma once
#include "__common.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "hitbox.hpp"

namespace p201
{

class quadtree
{
private:
    size_t _threshold;
    size_t _max_depth;
    size_t _max_objects;
    std::vector<quadtree> nodes;
       
public:
    quadtree(size_t threshold, size_t max_depth, size_t max_objects, world& world);
    ~quadtree() = default;
    void smash();
    
};

} // namespace p201
