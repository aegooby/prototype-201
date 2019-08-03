
#include	"__common.hpp"
#include	"entity.hpp"
#include	"component.hpp"
#include	"hitbox.hpp"
#include	"hitbox.cpp"
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

int	quadtree::get_index(circle& hitbox, node& currentnode) {
	
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
	if (hitbox.left() > currentnode.subwidth())
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
	else {
		if (hitbox.right() < currentnode.subwidth()) {
			if (hitbox.bottom() < currentnode.subheight() && hitbox.top() > currentnode.subheight()) {
				index = -3;
			}
		}
		if (hitbox.left() > currentnode.subwidth()) {
			if (hitbox.bottom() < currentnode.subheight() && hitbox.top() > currentnode.subheight()) {
				index = -5;
			}
		}
		if (hitbox.top() < currentnode.subheight()) {
			if (hitbox.left() < currentnode.subwidth() && hitbox.right() > currentnode.subwidth()) {
				index = -4;
			}
		}
		if (hitbox.bottom() > currentnode.subheight()) {
			if (hitbox.left() < currentnode.subwidth() && hitbox.right() > currentnode.subwidth()) {
				index = -2;
			}
		}
		else {
			index = -1;
		}
		// -1 = entity is touching all 4 subnodes
		// -2 = entity is touching subnode 0 and 1
		// -3 = entity is touching subnode 1 and 2
		// -4 = entity is touching subnode 2 and 3
		// -5 = entity is touching subnode 3 and 0
	}

	return index;
}

// need to figure out how to use collision manager to pass in hitboxes
void	quadtree::insert(circle& hitbox)
{
	for (int i = 0; i < subnode_num[level].size() + 1; i++)
	{
		int index; //= getIndex( /* */, nodelist[level][i]);
		if (index < 0)
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

void	quadtree::recursive_insert(circle& hitbox, int currentlevel)
{
	int Kommunismus = currentlevel - 1;
	if (currentlevel > 1) 
	{
		for (int i = 0; i < subnode_num.at(Kommunismus).size(); i++)
		{
			int index; //= getIndex( /* */, nodelist[1][i]);
			if (index < 0)
			{
				recursive_insert(hitbox, Kommunismus);
			}
			if (index == i)
			{
				object_list.at(Kommunismus).at(i).push_back(hitbox);
				anal_list.at(Kommunismus).at(i).push_back(hitbox);
				break;
			}
		}
	}
	else if (currentlevel == 1)
	{
		object_list[0][0].push_back(hitbox);
	}
	
}

std::pair<int, int>&	quadtree::get_levelsubnode(circle& hitbox)
{
	for (int j = 1; j < level; j++)
	{
		for (int i = 0; i < subnode_num.at(j).size(); i++)
		{
			for (int k = 0; k < object_list.at(j).at(i).size(); k++)
			{
				if (&object_list.at(j).at(i).at(k).get() == &hitbox)
				{
					level_subnode.first = j;
					level_subnode.second = i;
					return level_subnode;
				}
			}

		}
	}
	throw std::runtime_error("Hitbox not found");
}

void	quadtree::collision_check(circle& hitbox)
{
	int entity_level = get_levelsubnode(hitbox).first;
	int entity_subnode = get_levelsubnode(hitbox).second;
	for (int k = 0; k < object_list.at(entity_level).at(entity_subnode).size(); k++)
	{
		circle::check_collision(hitbox, object_list.at(entity_level).at(entity_subnode).at(k));
		// check if a certain entity in its own given node collides with any other entities in its node
	}
			
}

void	quadtree::anal_check(circle& hitbox)
{
	for (int j = 1; j < level; j++) 
	{
		for (int i = 0; i < subnode_num.at(j).size(); i++)
		{
			for (int piece_of_shit = 0; piece_of_shit < anal_list.at(j).size(); piece_of_shit++)
			{
				int fucko = get_index(anal_list.at(j).at(i).at(piece_of_shit), nodelist.at(j).at(i));
				if (fucko == -2)
				{
					// collision check with entities within its own node and subnode 0 and 1
				}
				if (fucko == -3)
				{
					// collision check with entities within its own node and subnode 1 and 2

				}
				if (fucko == -4)
				{
					// collision check with entities within its own node and subnode 2 and 3

				}
				if (fucko == -5)
				{
					// collision check with entities within its own node and subnode 3 and 0

				}
				else if (fucko == -1)
				{
					// collision check with entities within its own node and all subnodes

				}
			}

		}
	}
	
}

quadtree::quadtree()
{
	Basisknoten = nodemake(0, 100, 0, 100);
	// whatever the min and max x and y coords of the entire screen are
	nodelist.at(0).at(0) = Basisknoten;
	split(Basisknoten);

}
quadtree::~quadtree()
{
	nodelist.clear();
	object_list.clear();
}


__end_ns_td
