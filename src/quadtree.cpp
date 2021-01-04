#include "quadtree.hpp"

#include "__common.hpp"
#include "entity.hpp"
#include "linalg.hpp"
#include "system.hpp"
#include "world.hpp"

#include <algorithm>

namespace p201
{
bool quadtree::intersect(std::size_t id, const box& box)
{
    auto& entity = world.entity(id);
    auto& hitbox = entity.component<components::collision>().hitbox;

    std::unique_ptr<struct hitbox> ptr = std::make_unique<hitboxes::square>();
    auto& node = *dynamic_cast<hitboxes::square*>(ptr.get());

    node.width  = box.w;
    node.height = box.h;
    node.center = vector_3(box.x + box.w / 2.0f, box.y + box.h / 2.0f, 0.0f);
    return systems::collision::hitbox_check(hitbox, ptr);
}
void quadtree::insert(std::size_t id, node& node, std::size_t depth)
{
    if (!intersect(id, node.bounds)) { return; }
    if (node.leaf)
    {
        if (depth < max_depth && node.count() + 1 > threshold)
        {
            split(node);
            insert(id, node, depth);
        }
        else
            node.entities().emplace_back(id);
    }
    else
    {
        for (auto& child : node.children())
            if (intersect(id, child.bounds)) insert(id, child, depth + 1);
    }
}
void quadtree::remove(std::size_t id, node& node)
{
    if (node.leaf)
    {
        auto& entities = node.entities();
        std::erase(entities, id);
    }
    else
    {
        std::size_t total = 0;
        for (auto& child : node.children())
        {
            remove(id, child);
            total += child.count();
        }
        if (total < threshold)
        {
            auto& entities = __entities.emplace_back();
            for (auto& child : node.children())
            {
                assert(child.leaf);
                for (auto& entity : child.entities())
                    entities.emplace_back(entity);
            }
            __nodes.erase(node.children_iter());
            node.leaf = true;
            node.data = --__entities.end();
        }
    }
}
void quadtree::split(node& node)
{
    assert(node.leaf);
    // Add new set of 4 nodes
    auto& children = __nodes.emplace_back();

    // Set up bounds for children
    children.at(0).bounds = node.bounds.top_left();
    children.at(1).bounds = node.bounds.top_right();
    children.at(2).bounds = node.bounds.bottom_left();
    children.at(3).bounds = node.bounds.bottom_right();

    auto& entities = node.entities();

    // Place entity ids into child nodes based on bounds
    for (auto& child : children)
    {
        __entities.emplace_back();
        child.data = --__entities.end();
        for (auto& id : entities)
            if (intersect(id, child.bounds)) child.entities().emplace_back(id);
    }

    // Remove double counted entity ids
    __entities.erase(node.entities_iter());

    // Reset parent node
    node.leaf = false;
    node.data = --__nodes.end();
}

void quadtree::insert(std::size_t id)
{
    insert(id, root, 1);
}
void quadtree::remove(std::size_t id)
{
    remove(id, root);
}
void quadtree::leaves(node& node, std::list<std::vector<std::size_t>>& list)
{
    if (node.leaf && node.count() > 1)
        list.emplace_back(node.entities());
    else if (!node.leaf)
        for (auto& child : node.children()) leaves(child, list);
}
std::list<std::vector<std::size_t>> quadtree::leaves()
{
    std::list<std::vector<std::size_t>> list;
    leaves(root, list);
    return list;
}
void quadtree::insert(std::unordered_set<std::size_t>& entities)
{
    for (auto& id : entities) insert(id);
}
void quadtree::remove(std::unordered_set<std::size_t>& entities)
{
    for (auto& id : entities) remove(id);
}

} // namespace p201
// RIP TSA_agent, 27/12/2020 - 29/12/2020
