
#pragma once
#include	"__common.hpp"
#include	"entity.hpp"
#include	"component.hpp"
#include	"hitbox.hpp"

__begin_ns_td

class	quadtree
{
public:
	struct node
	{
		float	x0; // leftern edge
		float	x1; // rightern edge
		float	y0; // bottom edge
		float	y1; // top edge

		float	subwidth()
		{
			return x1 / 2.0f;
		}
		float	subheight()
		{
			return y1 / 2.0f;
		}
	};
private:
	std::vector<std::vector<std::vector<std::reference_wrapper<hitbox>>>> object_list;
	std::vector<std::vector<std::vector<std::reference_wrapper<hitbox>>>> anal_list;
	std::vector<std::vector<node>> nodelist;
	std::vector<std::vector<int>> subnode_num;
	std::pair<int, int> level_subnode;
	int index;

	Node Basisknoten;
	int		level = 0;
	void	add_subnodes(int current_level) {
		for (int i = 1; i < 5; i++)
		{
			subnode_num[current_level].push_back(i);
		}
	}
	int		maxobj = 8;
	node	bounds; // boundary of the current node

	node	nodemake(float x0, float x1, float y0, float y1)
	{
		bounds.x0 = x0;
		bounds.x1 = x1;
		bounds.y0 = y0;
		bounds.y1 = y1;

		return bounds;
	};


public:
	quadtree();
	~quadtree();
	void	split(node& currentbound);
	int		get_index(hitbox& hitbox, node& currentnode);
	void	insert(hitbox& hitbox);
	void	recursive_insert(hitbox& hitbox);
	void	collision_check(hitbox& hitbox);
	void	anal_check(hitbox& hitbox);
	void	get_level(hitbox& hitbox);
	void	get_subnode(hitbox& hitbox);
};



__end_ns_td
