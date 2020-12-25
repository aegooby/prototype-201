
#include "quadtree.hpp"
#include "__common.hpp"
#include "linalg.hpp"

namespace p201
{
quadtree::quadtree(size_t threshold, size_t max_depth, size_t max_objects, size_t width, size_t height, vector_3 position) {
    _threshold   = threshold;
    _max_depth   = max_depth;
    _max_objects = max_objects;
    _width = width;
    _height = height;
    _position = position;
    
// width,height = 480, 360
}

void quadtree::add_nodes() {
    int half_width = _width/2;
    int half_height = _height/2;
    
    nodes[0] = std::make_unique<quadtree>(_threshold, _max_depth-1, _max_objects, half_width, half_height, vector_3(_position(1) + half_width, _position(2), 0));
    
    nodes[1] = std::make_unique<quadtree>(_threshold, _max_depth-1, _max_objects, half_width, half_height, vector_3(_position(1),  _position(2), 0));
    
    nodes[2] = std::make_unique<quadtree>(_threshold, _max_depth-1, _max_objects, half_width, half_height, vector_3(_position(1),  _position(2) - half_height,0));
    
    nodes[3] = std::make_unique<quadtree>(_threshold, _max_depth-1, _max_objects, half_width, half_height, vector_3(_position(1) + half_width, _position(2) - half_height,0));
}


void quadtree::populate(std::unordered_map<id_t, std::reference_wrapper<entity>> entities) {
    if (_threshold < entities.size()){
        add_nodes();
        for (int i = 0; i < 4; i++){
            
            //nodes[i]->populate();
        }
    }
    
}

void quadtree::get_entities(vector_3 position, std::unordered_map<id_t, std::reference_wrapper<entity>> entities) {
    
    
    for (auto& entity : entities){
        
    }
}

} // namespace p201
