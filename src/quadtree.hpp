#pragma once
#include	"__common.hpp"
#include	"entity.hpp"
#include	"component.hpp"
#include	"hitbox.hpp"
#include	"component.hpp"

typedef struct BoundingBox {
	float x0; // leftern edge
	float x1; // rightern edge
	float y0; // bottom edge
	float y1; // top edge

};

typedef struct Node {
	float x0; // leftern edge
	float x1; // rightern edge
	float y0; // bottom edge
	float y1; // top edge
	int currentlevel;
};


class Quadtree {
	private:
	std::vector<std::reference_wrapper<struct capsule&>> Object_List;
	std::vector<Node> nodelist;
	int level;

	public:
	Quadtree() {	
	
	};

	Node Nodemake(float x0, float x1, float y0, float y1) {
		Node knoten;
		knoten.x0 = x0;
		knoten.x1 = x1;
		knoten.y0 = y0;
		knoten.y1 = y1;

		return knoten;
	};

	void split(Node& level) {
		int subwidth = level.x1 / 2;
		int subheight = level.y1 / 2;
		
		Node* subNode = new Node[4];
		
		// nodes are labelled from 0 to 3 anticlockwise like unit circle
		subNode[0] = Nodemake(subwidth, level.x1, subheight, level.y1);
		subNode[1] = Nodemake(level.x0, subwidth, subheight, level.y1);
		subNode[2] = Nodemake(level.x0, subwidth, level.y0, subheight);
		subNode[3] = Nodemake(subwidth, level.x1, level.y0, subheight);

		for (int i = 0; i < 3; i++) {
			nodelist.push_back(subNode[i]);
		}

	}

	void EntityCheck() {

	}

	void NodeSetup() {
		// idk the min and max range for x and y coord values this is placeholder
		Nodemake(0, 100, 0, 100);
			
			

	}




	//clears the quadtree of all nodes and objects 
	~Quadtree() {
		for (int i = 0; i < nodelist.size; i++) {
			if (nodelist[i] != NULL) {
				nodelist[i] = NULL;
			}
		}
	}
};

