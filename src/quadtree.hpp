
#pragma once
#include	"__common.hpp"
#include	"entity.hpp"
#include	"component.hpp"
#include	"hitbox.hpp"
#include	"component.hpp"

__begin_ns_td

struct	bounding_box
{
	float	x0; // leftern edge
	float	x1; // rightern edge
	float	y0; // bottom edge
	float	y1; // top edge
};

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
	std::vector<std::vector<std::vector<std::reference_wrapper<capsule>>>> object_list;
	std::vector<std::vector<node>> nodelist;
	int		level;
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
	quadtree()
	{
		level = 0; // amount of divisions
		nodemake(0, 100, 0, 100); // whatever the min and max x and y coords of the entire screen are
		split();
	}
	~quadtree()
	{
		for (level; level >= 1; level--)
		{
			for (int i = 0; i < 4; i++)
			{
				// TODO: fix this shit retard
//				nodelist.erase[level][i];
			}
		}
		nodelist.clear(); // is this just what I did above but better?
	}

	void	split()
	{
		level++;

		// TODO: nigga what the fUCK are you doing with the memory here
//		node *subNode = new node[4];
		// TODO: nigga fix this too
//		subNode[0] = nodemake(bounds.subwidth(), bounds.x1, bounds.subheight(), bounds.y1);
//		subNode[1] = nodemake(bounds.x0, bounds.subwidth(), bounds.subheight(), bounds.y1);
//		subNode[2] = nodemake(bounds.x0, bounds.subwidth(), bounds.y0, bounds.subheight());
//		subNode[3] = nodemake(bounds.subwidth(), bounds.x1, bounds.y0, bounds.subheight());

		for (int i = 0; i < 4; i++)
		{
			// TODO: fix
//			nodelist.push_back[level][subNode[i]];
		}
	}

	int get_index(capsule& hitbox, node& currentnode) {
		int index = -1; // -1 means it doesnt fit in any subnode and belongs to parent node

		if (hitbox.right() < currentnode.subwidth())
		{
			if (hitbox.top() < currentnode.subheight())
			{
				index = 2; 
			}
			else if (hitbox.bottom() > currentnode.subheight())
			{
				index = 1;
			}
		}
		else if (hitbox.left() > currentnode.subwidth())
		{
			if (hitbox.top() < currentnode.subheight())
			{
				index = 3;
			}
			else if (hitbox.bottom() > currentnode.subheight())
			{
				index = 0;
			}
		}
		return index;
	}

	// need to figure out how to use collision manager to pass in hitboxes
	void	insert(capsule& hitbox)
	{
		for (int i = 0; i < 4; i++)
		{
			int index; //= getIndex( /* */, nodelist[1][i]);
			// TODO: dawg both of these ifs check the same thing retard
			if (index == i)
			{
				// TODO: fix this
//				object_list.push_back[1][i][hitbox];
			}
			if (index == i)
			{
				return;
			}
		}
	}
};



__end_ns_td
