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

int	quadtree::get_index(hitbox& hitbox, node& currentnode) {
	
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
void	quadtree::insert(hitbox& hitbox)
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

void	quadtree::recursive_insert(hitbox& hitbox, int& currentlevel)
{
	int Kommunismus = currentlevel - 1;
	if (currentlevel > 1) 
	{
		for (int i = 0; i < subnode_num[Kommunismus].size(); i++)
		{
			int index; //= getIndex( /* */, nodelist[1][i]);
			if (index < 0)
			{
				recursive_insert(hitbox, Kommunismus);
			}
			if (index == i)
			{
				object_list[Kommunismus][i].push_back(hitbox);
				anal_list[Kommunismus][i].push_back(hitbox);
				break;
			}
		}
	}
	if else (currentlevel == 1) 
	{
		object_list[0][0].push_back(hitbox);
	}
	
}

quadtree::get_levelsubnode(hitbox& hitbox)
{
	for (int j = 1; j < level; j++)
	{
		for (int i = 0; i < subnode_num[j].size(); i++)
		{
			for (int k = 0; k < object_list[j][i].size(); k++)
			{
				if (object_list[j][i][k] == this->hitbox)
				{
					level_subnode.first = j;
					level_subnode.second = i;
					return level_subnode&;
				}
			}

		}
	}
}

quadtree::collision_check(hitbox& hitbox)
{
	int entity_level = get_levelsubnode(hitbox).first;
	int entity_subnode = get_levelsubnode(hitbox).second;
	for (int k = 0; k < object_list[entity_level][entity_subnode].size(); k++)
	{
		check_collision(hitbox, object_list[entity_level][entity_subnode][k]);
		// check if a certain entity in its own given node collides with any other entities in its node
	}
			
}

quadtree::anal_check(hitbox& hitbox)
{
	for (int j = 1; j < level; j++) 
	{
		for (int i = 0; i < subnode_num[j].size(); i++)
		{
			for (int piece_of_shit = 0; piece_of_shit < anal_list[j].size(); piece_of_shit++)
			{
				int fucko = get_index(anal_list[j][i][piece_of_shit], nodelist[j][i]);
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
	nodelist[0][0] = Basisknoten;
	split(Basisknoten);

}
quadtree::~quadtree()
{
	nodelist.clear();
	object_list.clear();
}


__end_ns_td
