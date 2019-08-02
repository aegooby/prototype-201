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

	sub_node[0] = nodemake(currentbound.subwidth(), currentbound.x1, currentbound.subheight(), currentbound.y1);
	sub_node[1] = nodemake(currentbound.x0, currentbound.subwidth(), currentbound.subheight(), currentbound.y1);
	sub_node[2] = nodemake(currentbound.x0, currentbound.subwidth(), currentbound.y0, currentbound.subheight());
	sub_node[3] = nodemake(currentbound.subwidth(), currentbound.x1, currentbound.y0, currentbound.subheight());

	for (int i = 0; i < 4; i++)
	{
		nodelist[level].push_back(sub_node[i]);
	}
}

int	quadtree::get_index(capsule& hitbox, node& currentnode) {
	int index = -1;

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
void	quadtree::insert(capsule& hitbox)
{
	for (int i = 0; i < subnode_num[level].size() + 1; i++)
	{
		int index; //= getIndex( /* */, nodelist[1][i]);
		if (index == -1)
		{
			recursive_insert(hitbox, level);
			break;
		}
		if (index == i)
		{
			if (object_list[level][i].size() >= maxobj)
			{
				split(nodelist[level][i]);
				insert(hitbox);
			}
			else if (object_list[level][i].size() < maxobj)
			{
				object_list[level][i].push_back(hitbox);
				break;
			}
		}
	}
}

void	quadtree::recursive_insert(capsule& hitbox, int currentlevel) 
{
	int Kommunismus = currentlevel - 1;
	if (currentlevel > 1) 
	{
		for (int i = 0; i < subnode_num[Kommunismus].size(); i++)
		{
			int index; //= getIndex( /* */, nodelist[1][i]);
			if (index == -1)
			{
				recursive_insert(hitbox, Kommunismus);
			}
			if (index == i)
			{
				object_list[Kommunismus][i].push_back(hitbox);
				break;
			}
		}
	}
	if else (currentlevel == 1) 
	{
		object_list[0][0].push_back(hitbox);
	}
	
}

quadtree::quadtree()
{
	Basisknoten = (nodemake(0, 100, 0, 100);
	split(Basisknoten);
	nodelist[0][0] = Basisknoten;
	// whatever the min and max x and y coords of the entire screen are
}
quadtree::~quadtree()
{
	nodelist.clear();
	object_list.clear();
}

quadtree::collisioncheck(hitbox& hitbox)
{
	//	current_box.x0 = 5 + (hitbox.x - hitbox.radius);
	//	current_box.x1 = 5 + (hitbox.x + hitbox.radius);
	//	current_box.y0 = 5 + (hitbox.y - hitbox.radius);
	//	current_box.y1 = 5 + (hitbox.y + hitbox.radius);
	// 5 is a placeholder, idea is make the box slightly larger than the hitbox of the entity
}


__end_ns_td
