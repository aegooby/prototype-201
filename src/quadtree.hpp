#pragma once
#include	"__common.hpp"
#include	"entity.hpp"
#include	"component.hpp"
#include	"hitbox.hpp"
#include	"component.hpp"


class Quadtree {
	private:
	int Max_Objects = 6; // max amount of objects in a node
	int Current_Level;
	std::vector<std::reference_wrapper<struct capsule&>> Object_List;
	std::vector<int> nodes;

public:
	Quadtree() {	};

	static void clear() {
		for (int i = 0; i < nodes.size; i++) {
			if (nodes[i] != NULL) {
				clear();
				nodes[i] = NULL;
			}
		}
	}
};

