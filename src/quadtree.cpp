#include "quadtree.hpp"

#include "__common.hpp"
#include "entity.hpp"
#include "linalg.hpp"

namespace p201
{
quadtree::quadtree(std::string id, size_t max_depth, size_t max_objects,
                   size_t width, size_t height, vector_3 position)
{
    _id          = _id + id;
    _max_depth   = max_depth;
    _max_objects = max_objects;
    _width       = width;
    _height      = height;
    _position    = position;

    nodes[0] = nullptr; // means this quadtree has no nodes

}

void quadtree::add_nodes()
{
    size_t half_width_up    = (_width + 1) / 2;
    size_t half_height_up   = (_height + 1) / 2;
    size_t half_width_down  = _width / 2;
    size_t half_height_down = _height / 2;

    nodes[0] = std::make_unique<quadtree>(
        _id + "0", _max_depth - 1, _max_objects, half_width_up,
        half_height_down,
        vector_3(_position(0) + _width, _position(1) + half_height_down, 0));

    nodes[1] = std::make_unique<quadtree>(
        _id + "1", _max_depth - 1, _max_objects, half_width_down,
        half_height_down, vector_3(_position(0)+_width, _position(1), 0));

    nodes[2] = std::make_unique<quadtree>(
        _id + "2", _max_depth - 1, _max_objects, half_width_down,
        half_height_up,
        vector_3(_position(0) + half_width_down, _position(1), 0));

    nodes[3] = std::make_unique<quadtree>(
        _id + "3", _max_depth - 1, _max_objects, half_width_up, half_height_up,
        vector_3(_position(0) + half_width_down,
                 _position(1) + half_height_down, 0));
}


bool quadtree::border_control(vector_3& entity_position)
{
    if ((entity_position(0) == _position(0) &&
         entity_position(1) <= _position(1)  &&
         entity_position(1) <= _position(1) + _height) ||
        (entity_position(0) == _position(0) + _width &&
         _position(1) <= entity_position(1) &&
         entity_position(1) <= _position(1) + _height) ||
        (entity_position(1) == _position(1) &&
         _position(0) <= entity_position(0) &&
         entity_position(0) <= _position(0) + _width) ||
        (entity_position(1) == _position(1) + _height &&
         _position(0) <= entity_position(0) &&
         entity_position(0) <= _position(0) + _width))
    {

        return true;
    }
    return false;
}

bool quadtree::addable()
{
    if (node_entities.size() < _max_objects || _max_depth == 0)
    {
        return true; // add entity at current node
    }
    else
    {
    return false; // create subnodes and add entity at a subnode }
    }
}


bool quadtree::in_node(entity& entity, vector_3& node_position, size_t width, size_t height) {
    vector_3& entity_position = entity.component<components::transform>().position;
    if ((node_position(0)- width <= entity_position(0)) &&
    (entity_position(0) <= node_position(0)) &&
    (node_position(1) <= entity_position(1)) &&
    (entity_position(1) <= node_position(1) + height))
    {
        std::cout << "ENTITY " << entity.id << " IS IN NODE " + _id << std::endl;
        return true;
    }
    else {
        return false;
    }
}

quadtree& quadtree::get_node(std::string node_id) {
    if (node_id.size() == 0) {
        return *this;
    }

    else if (node_id[0] == '0') {
        return nodes[0]->get_node(node_id.erase(0,1));
    }

    else if (node_id[0] == '1') {
        return nodes[1]->get_node(node_id.erase(0,1));
    }

    else if (node_id[0] == '2') {
        return nodes[2]->get_node(node_id.erase(0,1));
    }
    else {
        return nodes[3]->get_node(node_id.erase(0,1));
    }

}

std::vector<std::string> quadtree::curr_locate(entity& entity)
{
    std::vector<std::string> node_vec;

    if (in_node(entity, _position, _width, _height)) {
        for (auto& node_pair : node_entities){
            if (node_pair.second.get().id == entity.id) {
                node_vec.emplace_back(_id);
            }
        }
    }

    if (nodes[0] != nullptr) {
        for (int i = 0; i < 4; i++)
        {
            if (nodes[i]->in_node(entity, nodes[i]->_position, nodes[i]->_width, nodes[i]->_height))
            {
                std::vector<std::string> temp = nodes[i]->curr_locate(entity);
                node_vec.insert(node_vec.end(), temp.begin(), temp.end());
            }

        }
    }
        
    
    return node_vec;
}

std::vector<std::string> quadtree::new_locate(entity& entity)
{
    std::vector<std::string> node_vec;

    if (in_node(entity, _position, _width, _height)) {
        if (nodes[0] == nullptr && addable())
        {
            node_vec.emplace_back(_id);
        }

        else
        {
            if (nodes[0] == nullptr && node_entities.size() >= _max_objects) { add_nodes(); }
            for (int i = 0; i < 4; i++)
            {
                if (nodes[i]->in_node(entity, nodes[i]->_position, nodes[i]->_width, nodes[i]->_height)) {
                    std::vector<std::string> temp = nodes[i]->new_locate(entity);
                    node_vec.insert(node_vec.end(), temp.begin(), temp.end());
                }

            }
        }
    }

    return node_vec;
}


void quadtree::remove_entity(entity& entity, std::vector<std::string> node_ids) {
    for (std::string id : node_ids) {
        quadtree& node = get_node(id);

        for (auto& node_pair : node.node_entities){
            if (node_pair.second.get().id == entity.id) {
                node.node_entities.erase(node_pair.first);
            }
        }
    }

}

void quadtree::add_entity(entity& entity, std::vector<std::string> node_ids)
{
    for (std::string id : node_ids) {
        quadtree& node = get_node(id);
        node.node_entities.emplace(_id, entity);
    }

}

void quadtree::update(entity& entity) {

    std::vector<std::string> new_nodes = new_locate(entity);
    std::vector<std::string> curr_nodes = curr_locate(entity);

    if (new_nodes != curr_nodes){
        remove_entity(entity, curr_nodes);
        add_entity(entity, new_nodes);
    }

}

} // namespace p201
// RIP TSA_agent, 27/12/2020 - 29/12/2020
