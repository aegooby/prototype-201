
#pragma once
#include "__common.hpp"
#include "component.hpp"

#include <bitset>
#include <typeindex>
#include <unordered_map>
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
    enum flag
    {
        unknown   = 0x0,
        render    = 0x1,
        transform = 0x2,
        movement  = 0x4,
        collision = 0x5,
        input     = 0x6,
        audio     = 0x7,
    };
    using flag_map_t = std::unordered_map<std::type_index, system::flag>;
    /** @brief Conversion table between component types and flags. */
    inline static const flag_map_t flags = {
        { typeid(render_component), system::flag::render },
        { typeid(transform_component), system::flag::transform },
        { typeid(movement_component), system::flag::movement },
        { typeid(collision_component), system::flag::collision },
        { typeid(input_component), system::flag::input },
    };
    /** @brief The flag bitset associated with this system instance. */
    std::bitset<flag_bits> flag;

protected:
    std::unordered_map<id_t, std::reference_wrapper<entity>>
                 __registered_entities;
    class world& world;

public:
    system(class world& world) : world(world) { }
    virtual ~system() = default;
    /** @brief All the needed system initialization. */
    virtual void start() = 0;
    /** @brief Called periodically to update registered entities. */
    virtual void update() = 0;
    void         register_entity(class entity&);
    void         deregister_entity(class entity&);

    // Preventing copying and moving
    system(const system&) = delete;
    system(system&&)      = delete;
    system& operator=(const system&) = delete;
    system& operator=(system&&) = delete;
};

} // namespace p201
