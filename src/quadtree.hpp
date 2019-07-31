#pragma once
#include	"__common.hpp"
#include	"entity.hpp"
#include	"component.hpp"
#include	"hitbox.hpp"
#include	"component.hpp"

struct BoundingBox {
	float x0; // leftern edge
	float x1; // rightern edge
	float y0; // bottom edge
	float y1; // top edge

};

struct Node {
	float x0; // leftern edge
	float x1; // rightern edge
	float y0; // bottom edge
	float y1; // top edge
	int currentlevel;
};


class Quadtree {
	private:

	std::vector<std::reference_wrapper<struct capsule&>> Object_List;
	std::vector<std::vector<Node*>> nodelist;
	int level;
	Node bounds;

	Node Nodemake(float x0, float x1, float y0, float y1) {
		Node knoten;
		knoten.x0 = x0;
		knoten.x1 = x1;
		knoten.y0 = y0;
		knoten.y1 = y1;

		return knoten;
	};

	public:

	Quadtree() {	
		level = 0;	// amount of divisions
		Nodemake(0, 100, 0, 100);
	}

	void split(Node& currentlevel) {
		level++;
		int subwidth = currentlevel.x1 / 2;
		int subheight = currentlevel.y1 / 2;
		
		Node *subNode = new Node[4];
		// nodes are labelled from 0 to 3 anticlockwise like unit circle
		subNode[0] = Nodemake(subwidth, currentlevel.x1, subheight, currentlevel.y1);
		subNode[1] = Nodemake(currentlevel.x0, subwidth, subheight, currentlevel.y1);
		subNode[2] = Nodemake(currentlevel.x0, subwidth, currentlevel.y0, subheight);
		subNode[3] = Nodemake(subwidth, currentlevel.x1, currentlevel.y0, subheight);

		for (int i = 0; i < 3; i++) {
			nodelist.push_back[level][subNode[i]];
		}

	}

	int getIndex(capsule& hitbox) {
		int index;

		// if the hitbox fits in 0 quadrant
		if (hitbox.x < x0) {

		}

	}

	bool EntityCheck() {



		// if there are more than 5 entities in the node
		if () {

			return true;
		}
		// if there are less than 5 entities in the node
		else {
			return false;
		}
	}




	//clears the quadtree of all nodes and objects 
	~Quadtree() {
		for (level; level >= 1; level--) {
			for (int i = 0; i < 4; i++) {
				nodelist[level][i] = nullptr;
			}
		}
	}
};

