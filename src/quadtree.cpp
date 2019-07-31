#include	"__common.hpp"
#include	"entity.hpp"
#include	"component.hpp"
#include	"hitbox.hpp"
#include	"component.hpp"
#include	"quadtree.hpp"


BoundingBox	Quadtree::Boxmake(float x0, float x1, float y0, float y1) {
		BoundingBox bbox;
		bbox.x0 = x0;
		bbox.x1 = x1;
		bbox.y0 = y0;
		bbox.y1 = y1;

		return bbox;
}

Node Quadtree::NodeDataMake(float latitude, float longitude, void *data) {	
	Node nodedata;
	nodedata.latitude = latitude;
	nodedata.longitude = longitude;
	nodedata.data = data;

	return nodedata;
};


Quadtree::~Quadtree() {
	for (int i = 0; i < nodes.size; i++) {
		if (nodes[i] != NULL) {
			nodes[i] = NULL;
		}
}