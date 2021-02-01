
#pragma once
#include "../../__common.hpp"
#include "../component.hpp"
#include "../entity.hpp"

#include <bitset>
#include <typeindex>
#include <unordered_set>
#include <vector>

namespace p201
{

class system
{
public:
    /** @brief The flag bitset associated with this system instance. */
    std::bitset<entity::flag_bits> flag;

protected:
    class world& world;
    /** @brief Entities that are registered for this system. */
    std::unordered_set<std::size_t> __registered_entities;

public:
    system(class world& world) : world(world) { }
    virtual ~system() = 0;
    /** @brief All the needed system initialization. */
    virtual void start();
    /** @brief Called periodically to update registered entities. */
    virtual void update([[maybe_unused]] float dt);

    virtual void register_entity(entity::id_t);
    virtual void deregister_entity(entity::id_t);

    system(const system&) = delete;
    system(system&&)      = delete;
    system& operator=(const system&) = delete;
    system& operator=(system&&) = delete;
};

} // namespace p201
