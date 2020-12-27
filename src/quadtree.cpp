#include "quadtree.hpp"

#include "__common.hpp"
#include "linalg.hpp"
#include "entity.hpp"

namespace p201
{
quadtree::quadtree(std::string id, size_t max_depth, size_t max_objects, size_t width, size_t height, vector_3 position) {
    _id          = _id + id;
    _max_depth   = max_depth;
    _max_objects = max_objects;
    _width = width;
    _height = height;
    _position = position;
    
    nodes[0] = nullptr;                 // means this quadtree has no nodes
    
// width,height = 480, 360
}

void quadtree::add_nodes() {
    size_t half_width_up = (_width+1)/2;
    size_t half_height_up = (_height+1)/2;
    size_t half_width_down = _width/2;
    size_t half_height_down = _height/2;
    
    nodes[0] = std::make_unique<quadtree>(_id + "0", _max_depth-1, _max_objects, half_width_up, half_height_down, vector_3(_position(0) + half_width_down, _position(1), 0));
    
    nodes[1] = std::make_unique<quadtree>(_id + "1", _max_depth-1, _max_objects, half_width_down, half_height_down, vector_3(_position(0),  _position(1), 0));
    
    nodes[2] = std::make_unique<quadtree>(_id + "2", _max_depth-1, _max_objects, half_width_down, half_height_up, vector_3(_position(0),  _position(1) - half_height_down,0));
    
    nodes[3] = std::make_unique<quadtree>(_id + "3", _max_depth-1, _max_objects, half_width_up, half_height_up, vector_3(_position(0) + half_width_down, _position(1) - half_height_down,0));
}


std::string quadtree::add_entity(entity& entity) {
    vector_3 entity_position = entity.component<transform_component>().position;
    
    if ( (_position(0) <= entity_position(0)) && (entity_position(0) <= _position(0)+_width) && (_position(1)-_height <= entity_position(1)) && (entity_position(1) <= _position(1))) {
        
        if (nodes[0] == nullptr && addable()) {
            node_entities.emplace(entity.id, entity);
            return _id;
        } // return the id of smallest node
        
        else {
            if (nodes[0] == nullptr){
                add_nodes();
            }
            
            int TSA_agent = -1; // if entity is at border, makes sure it gets added to all required subnodes
            for (int i = 0; i < 4; i++){
                std::string check = nodes[i]->add_entity(entity);
                    if (nodes[i]->border_control(entity_position)){
                        check = "-1";
                        TSA_agent = i;
                    }
                    if (i == 3 && TSA_agent != -1){
                        check = std::to_string(TSA_agent);
                    }
                    if (check != "-1") {
                        return check;
                    }
                }
            
            }
        }
    
    return "-1";
    //only time this function returns "-1" is during recursive call, raise error if it returns "-1" as a whole, that means quadtree generation or entity position vector is wrong
}

bool quadtree::border_control(vector_3 entity_position) {
    if (
        (entity_position(0) ==_position(0) && _position(1) - _height <= entity_position(1)
         && entity_position(1) <=_position(1)) ||
        (entity_position(0) ==_position(0) + _width && _position(1) - _height <= entity_position(1)
        && entity_position(1) <=_position(1)) ||
        (entity_position(1) ==_position(1) && _position(0) <= entity_position(0)
        && entity_position(0) <=_position(0) + _width) ||
        (entity_position(1) ==_position(1) - _height && _position(0) <= entity_position(0)
        && entity_position(0) <=_position(0) + _width) ) {
        
        return true;
    }
    return false;
}

bool quadtree::addable() {
    if (node_entities.size() < _max_objects || _max_depth == 0) {
        return true; // add entity at current node
    }
    else {
        return false; // create subnodes and add entity at a subnode
    }
}

} // namespace p201
