
#include "quadtree.hpp"

#include "__common.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "hitbox.hpp"

namespace p201
{
quadtree::quadtree(size_t threshold, size_t max_depth, size_t max_objects,
                   class world& world)
{
    _threshold   = threshold;
    _max_depth   = max_depth;
    _max_objects = max_objects;
};

} // namespace p201
