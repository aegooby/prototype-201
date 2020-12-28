
#pragma once
#include "__common.hpp"
#include "entity.hpp"
#include "linalg.hpp"

#include <unordered_map>

namespace p201
{

class quadtree
{
private:
    std::string _id;
    size_t      _max_depth;
    size_t      _max_objects;
    size_t      _width;
    size_t      _height;
    vector_3    _position; // top left x & y pos

    std::unique_ptr<quadtree>                                nodes[4];
    std::unordered_map<std::string, std::reference_wrapper<entity>> node_entities;

public:
    quadtree(std::string id, size_t max_depth, size_t max_objects, size_t width,
             size_t height, vector_3 position);
    // at beginning, call with id = ""

    ~quadtree() = default;
    void add_nodes();
    bool addable();

    bool        border_control(vector_3 entity_position);
    std::string add_entity(entity& entity);
    // called when adding/moving entities, places entity in correct node
    
    void remove_entity(entity& entity, std::string node_id);
};

} // namespace p201
