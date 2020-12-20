//
//#include    "__common.hpp"
//#include    "entity.hpp"
//#include    "component.hpp"
//#include    "hitbox.hpp"
//#include    "hitbox.cpp"
//#include    "component.hpp"
//#include    "quadtree.hpp"
//
// namespace p201 {
//
// void    quadtree::split(node& currentbound)
//{
//    level++;
//    add_subnodes(level);
//    std::unique_ptr<node[]> sub_node = std::make_unique<node[]>(5);
//
//    sub_node[0] = nodemake(currentbound.subwidth(), currentbound.x1,
//    currentbound.subheight(), currentbound.y1); sub_node[1] =
//    nodemake(currentbound.x0, currentbound.subwidth(),
//    currentbound.subheight(), currentbound.y1); sub_node[2] =
//    nodemake(currentbound.x0, currentbound.subwidth(), currentbound.y0,
//    currentbound.subheight()); sub_node[3] = nodemake(currentbound.subwidth(),
//    currentbound.x1, currentbound.y0, currentbound.subheight());
//
//    for (int i = 0; i < 4; i++)
//    {
//        nodelist[level].push_back(sub_node[i]);
//    }
//}
//
// int    quadtree::get_index(circle& hitbox, node& currentnode) {
//
//    if (currentnode == Basisknoten)
//    {
//        index = 0;
//    }
//
//    if (hitbox.right() <= currentnode.subwidth())
//    {
//        if (hitbox.top() <= currentnode.subheight())
//        {
//            index = 2;
//        }
//        else if (hitbox.bottom() >= currentnode.subheight())
//        {
//            index = 1;
//        }
//    }
//
//    if (hitbox.left() >= currentnode.subwidth())
//    {
//        if (hitbox.top() <= currentnode.subheight())
//        {
//            index = 3;
//        }
//        else if (hitbox.bottom() >= currentnode.subheight())
//        {
//            index = 0;
//        }
//    }
//
//    if (hitbox.right() > currentnode.subwidth() && hitbox.left() <
//    currentnode.subwidth()) {
//        if (hitbox.top() <= currentnode.subheight())
//        {
//            index = 2;
//        }
//        else if (hitbox.bottom() >= currentnode.subheight())
//        {
//            index = 0;
//        }
//    }
//
//    if (hitbox.top() > currentnode.subheight() && hitbox.bottom() <
//    currentnode.subheight()) {
//        if (hitbox.right() <= currentnode.subwidth())
//        {
//            index = 1;
//        }
//        else if (hitbox.left() >= currentnode.subwidth())
//        {
//            index = 3;
//        }
//    }
//
//    else {
//        index = 0;
//    }
//
//    return index;
//}
//
// void    quadtree::insert(circle& hitbox, int& currentlevel)
//{
//    int antes = currentlevel - 1;
//    for (int i = 0; i < subnode_num.at(antes).size(); i++)
//    {
//        int index = get_index(hitbox, nodelist.at(antes).at(i));
//        if (index == i)
//        {
//            if (object_list[currentlevel][i].size() >= maxobj)
//            {
//                split(nodelist.at(currentlevel).at(i));
//                insert(hitbox, currentlevel + 1);
//            }
//            else if (object_list[currentlevel][i].size() < maxobj)
//            {
//                object_list[currentlevel][i].push_back(hitbox);
//                break;
//            }
//        }
//    }
//
//
//}
//
//
// void    quadtree::recursive_insert(circle& hitbox, int currentlevel)
//{
//    int Kommunismus = currentlevel - 1;
//    if (currentlevel > 1)
//    {
//        for (int i = 0; i < subnode_num.at(Kommunismus).size(); i++)
//        {
//            int index = get_index(hitbox, nodelist[1][i]);
//            if (index < 0)
//            {
//                recursive_insert(hitbox, Kommunismus);
//            }
//            if (index == i)
//            {
//                object_list.at(Kommunismus).at(i).push_back(hitbox);
//                break;
//            }
//        }
//    }
//    else if (currentlevel == 1)
//    {
//        object_list[0][0].push_back(hitbox);
//    }
//
//}
//
// std::pair<int, int>&    quadtree::get_levelsubnode(circle& hitbox)
//{
//    for (int j = 1; j < level; j++)
//    {
//        for (int i = 0; i < subnode_num.at(j).size(); i++)
//        {
//            for (int k = 0; k < object_list.at(j).at(i).size(); k++)
//            {
//                if (&object_list.at(j).at(i).at(k).get() == &hitbox)
//                {
//                    level_subnode.first = j;
//                    level_subnode.second = i;
//                    return level_subnode;
//                }
//            }
//
//        }
//    }
//    throw std::runtime_error("Hitbox not found");
//}
//
// void    quadtree::collision_check(circle& hitbox)
//{
//    int entity_level = get_levelsubnode(hitbox).first;
//    int entity_subnode = get_levelsubnode(hitbox).second;
//    for (int k = 0; k <
//    object_list.at(entity_level).at(entity_subnode).size(); k++)
//    {
//        circle::check_collision(hitbox,
//        object_list.at(entity_level).at(entity_subnode).at(k));
//        // check if a certain entity in its own given node collides with any
//        other entities in its node
//    }
//
//}
//
// void    total_collision_check(std::vector<std::unique_ptr<class component>>&
// hitbox)
//{
//    for (int j = 0; j < hitbox.size(); j++)
//    {
//        insert(hitbox.at(j), 1);
//    }
//
//    for (int i = 0; i < object_list.at(0).at(0).size(); i++)
//    {
//        anal_check();
//    }
//
//    for (int i = 1; i < level; i++)
//    {
//        for (int k = 0; k < subnode_num.at(i).size(); k++)
//        {
//            for (int j = 0; j < hitbox.size(); j++)
//            {
//                int index = get_index(hitbox.at(j), nodelist[Osama][i]);
//            }
//        }
//    }
//
//    collision_check(hitbox.at(j));
//
//}
//
// quadtree::quadtree()
//{
//    Basisknoten = nodemake(0, 100, 0, 100);
//    // whatever the min and max x and y coords of the entire screen are
//
//    for (int i = 0; i < 4; i++)
//    {
//        nodelist.at(0).push_back(Basisknoten);
//    }
//    split(Basisknoten);
//
//}
// quadtree::~quadtree()
//{
//    nodelist.clear();
//    object_list.clear();
//}
//
//
//} //namespace p201
