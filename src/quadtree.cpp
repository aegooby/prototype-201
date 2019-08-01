#include	"__common.hpp"
#include	"entity.hpp"
#include	"component.hpp"
#include	"hitbox.hpp"
#include	"component.hpp"
#include	"quadtree.hpp"

__begin_ns_td




	void	quadtree::split(node& currentbound)
	{
		level++;
		add_subnodes(level);
		std::unique_ptr<node[]> sub_node = std::make_unique<node[]>(5);

		sub_node[1] = nodemake(currentbound.subwidth(), currentbound.x1, currentbound.subheight(), currentbound.y1);
		sub_node[2] = nodemake(currentbound.x0, currentbound.subwidth(), currentbound.subheight(), currentbound.y1);
		sub_node[3] = nodemake(currentbound.x0, currentbound.subwidth(), currentbound.y0, currentbound.subheight());
		sub_node[4] = nodemake(currentbound.subwidth(), currentbound.x1, currentbound.y0, currentbound.subheight());

		for (int i = 1; i < 5; i++)
		{
			nodelist[level].push_back(sub_node[i]);
		}
	}

	int quadtree::get_index(capsule& hitbox, node& currentnode) {
		int index = -1;

		if (hitbox.right() < currentnode.subwidth())
		{
			if (hitbox.top() < currentnode.subheight())
			{
				index = 3;
			}
			else if (hitbox.bottom() > currentnode.subheight())
			{
				index = 2;
			}
		}
		else if (hitbox.left() > currentnode.subwidth())
		{
			if (hitbox.top() < currentnode.subheight())
			{
				index = 4;
			}
			else if (hitbox.bottom() > currentnode.subheight())
			{
				index = 1;
			}
		}
		return index;
	}

	// need to figure out how to use collision manager to pass in hitboxes
	void	quadtree::insert(capsule& hitbox)
	{
		for (int i = 1; i < subnode_num[level].size() + 1; i++)
		{
			int index; //= getIndex( /* */, nodelist[1][i]);
			if (index == -1)
			{
				object_list[level - 1][0].push_back(hitbox);
				break;
			}
			if (index == i)
			{
				if (object_list[level][i].size() > maxobj)
				{
					split(nodelist[level][i]);
					insert(hitbox);
				}
				if else (object_list[level][i].size() <= maxobj)
				{
					object_list[level][i].push_back(hitbox);
					break;
				}
			}
		}



	}

	quadtree::quadtree()
	{
		split(nodemake(0, 100, 0, 100));
		// whatever the min and max x and y coords of the entire screen are
	}
	quadtree::~quadtree()
	{
		nodelist.clear();
		object_list.clear();
	}

__end_ns_td
