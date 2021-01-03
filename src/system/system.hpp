
#pragma once
#include "../__common.hpp"
#include "../component.hpp"

#include <bitset>
#include <typeindex>
#include <unordered_set>
#include <vector>

namespace p201
{

/**
 * @brief Systems are one third of the ECS architecture. Whereas entities are
 *        groupings of components, and components are simply data, systems
 *        contain the logic for operating on this data and manipulating it.
 *        Systems contain no data other than their flags, in the same way that
 *        components contain no logic.
 */
class system
{
public:
    /** @brief The flag bitset associated with this system instance. */
    std::bitset<component::flag_bits> flag;

protected:
    class world& world;
    /** @brief Entities that are registered for this system. */
    std::unordered_set<std::size_t> __registered_entities;

public:
    system(class world& world) : world(world) { }
    virtual ~system() = default;
    /** @brief All the needed system initialization. */
    virtual void start() = 0;
    /** @brief Called periodically to update registered entities. */
    virtual void update(float dt) = 0;
    virtual void register_entity(class entity&);
    virtual void deregister_entity(class entity&);

    // Preventing copying and moving
    system(const system&) = delete;
    system(system&&)      = delete;
    system& operator=(const system&) = delete;
    system& operator=(system&&) = delete;
};

} // namespace p201
