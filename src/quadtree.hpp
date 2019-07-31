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

	float getsubwidth()	{
		return subwidth;
	}
	float getsubheight() {
		return subheight;
	}
};


class Quadtree {
	private:

	std::vector<std::reference_wrapper<struct capsule&>> Object_List;
	std::vector<std::vector<Node*>> nodelist;
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
		Nodemake(0, 100, 0, 100);
	}

	void split() {
		level++;

		Node *subNode = new Node[4];
		// nodes are labelled from 0 to 3 anticlockwise like unit circle
		subNode[0] = Nodemake(bounds.getsubwidth(), bounds.getx1(), bounds.getsubheight(), bounds.gety1());
		subNode[1] = Nodemake(bounds.getx0(), bounds.getsubwidth(), bounds.getsubheight(), bounds.gety1());
		subNode[2] = Nodemake(bounds.getx0(), bounds.getsubwidth(), bounds.gety0(), bounds.getsubheight());
		subNode[3] = Nodemake(bounds.getsubwidth(), bounds.getx1(), bounds.gety0(), bounds.getsubheight());

		for (int i = 0; i < 3; i++) {
			nodelist.push_back[level][subNode[i]];
		}

	}

	int getIndex(capsule& hitbox, Node& bounds) {
		int index = -1; // -1 means it doesnt fit in any subnode and belongs to parent node

		if (hitbox.getright() < bounds.getsubwidth()) {
			if (hitbox.gettop() < bounds.getsubheight()) {
				index = 2; // belongs to subnode 2
			}
			else if (hitbox.gety() > bounds.getsubheight()) {
				index = 1;
			}
		}
		else if (hitbox.getx() > bounds.getsubwidth()) {
			if (hitbox.gettop() < bounds.getsubheight()) {
				index = 3;
			}
			else if (hitbox.gety() > bounds.getsubheight()) {
				index = 0;
			}
		}

		return index;

	}

	void insert() {

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

