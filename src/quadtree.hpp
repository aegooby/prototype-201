#pragma once
#include	"__common.hpp"
#include	"entity.hpp"
#include	"component.hpp"
#include	"hitbox.hpp"
#include	"component.hpp"

__begin_ns_td

struct BoundingBox {
	float x0; // leftern edge
	float x1; // rightern edge
	float y0; // bottom edge
	float y1; // top edge

};




class Quadtree {
	private:
	struct Node {
		float x0; // leftern edge
		float x1; // rightern edge
		float y0; // bottom edge
		float y1; // top edge

		float getx0() {
			return x0;
			}
		float getx1() {
			return x1;
		}
		float gety0() {
			return y0;
		}
		float gety1() {
			return y1;
		}

		float subwidth = getx1() / 2;
		float subheight = gety1() / 2;

		float getsubwidth() {
			return subwidth;
		}
		float getsubheight() {
			return subheight;
		}
	};

	std::vector<std::vector<std::vector<std::reference_wrapper<struct capsule>>>> Object_List;
	std::vector<std::vector<Node>> nodelist;
	int level;
	Node bounds;  // boundary of the current node


	Node Nodemake(float x0, float x1, float y0, float y1) {
		bounds.x0 = x0;
		bounds.x1 = x1;
		bounds.y0 = y0;
		bounds.y1 = y1;

		return bounds;
	};

	public:

	Quadtree() {	
		level = 0;	// amount of divisions
		Nodemake(0, 100, 0, 100); // whatever the min and max x and y coords of the entire screen are
		split();
	}

	void split() {
		level++;

		Node *subNode = new Node[4];
		// nodes are labelled from 0 to 3 anticlockwise like unit circle
		subNode[0] = Nodemake(bounds.getsubwidth(), bounds.getx1(), bounds.getsubheight(), bounds.gety1());
		subNode[1] = Nodemake(bounds.getx0(), bounds.getsubwidth(), bounds.getsubheight(), bounds.gety1());
		subNode[2] = Nodemake(bounds.getx0(), bounds.getsubwidth(), bounds.gety0(), bounds.getsubheight());
		subNode[3] = Nodemake(bounds.getsubwidth(), bounds.getx1(), bounds.gety0(), bounds.getsubheight());

		for (int i = 0; i < 4; i++) {
			nodelist.push_back[level][subNode[i]];
		}

	}

	int getIndex(capsule& hitbox, Node& currentnode) {
		int index = -1; // -1 means it doesnt fit in any subnode and belongs to parent node

		if (hitbox.getright() < currentnode.getsubwidth()) {
			if (hitbox.gettop() < currentnode.getsubheight()) {
				index = 2; 
			}
			else if (hitbox.gety() > currentnode.getsubheight()) {
				index = 1;
			}
		}
		else if (hitbox.getx() > currentnode.getsubwidth()) {
			if (hitbox.gettop() < currentnode.getsubheight()) {
				index = 3;
			}
			else if (hitbox.gety() > currentnode.getsubheight()) {
				index = 0;
			}
		}

		return index;

	}

	// need to figure out how to use collision manager to pass in hitboxes
	void insert(capsule& hitbox) {
		for (int i = 0; i < 4; i++) {
			int index = getIndex( /* */, nodelist[1][i]);
			if (index == i) {
				Object_List.push_back[1][i][hitbox];
			}
			if (index == i) {

			return;
		}
		}
		
	
	}
		



	//clears the quadtree of all nodes and objects 
	~Quadtree() {
		
		for (level; level >= 1; level--) {
			for (int i = 0; i < 4; i++) {
				nodelist.erase[level][i];
			}
		} 
		
		nodelist.clear; // is this just what I did above but better?

	}
}



__end_ns_td