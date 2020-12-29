
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
    
    bool addable();
    bool border_control(vector_3 entity_position);
    bool in_node(vector_3 entity_position, vector_3 node_position, size_t width, size_t height);
    
    void add_nodes();
    void add_entity(entity& entity, std::vector<std::string> node_ids);
    void remove_entity(entity& entity, std::vector<std::string> node_ids);
    
    void update(entity& entity);
    std::vector<std::string> curr_locate(entity& entity); // returns all node_id that currently has entity
    std::vector<std::string> new_locate(entity& entity); // returns all node_id that should have entity
    quadtree& get_node(std::string node_id); // returns node when given node_id
    
};

} // namespace p201
