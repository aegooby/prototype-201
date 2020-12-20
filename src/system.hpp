
#pragma once
#include "__common.hpp"

#include <bitset>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace p201
{

class system_flag : public std::bitset<32>
{
public:
    using __base = std::bitset<32>;

public:
    constexpr system_flag() noexcept = default;
    constexpr system_flag(unsigned long long val) noexcept : __base(val) { }
    ~system_flag() = default;
};

class system
{
public:
    enum flag
    {
        unknown   = 0x0,
        render    = 0x1,
        transform = 0x2,
        collision = 0x3,
        input     = 0x4,
        audio     = 0x5,
        state     = 0x6,
    };
    static const std::unordered_map<std::type_index, system::flag> flags;
    system_flag                                                    flag;

protected:
    std::unordered_map<id_t, std::reference_wrapper<entity>>
                 __registered_entities;
    class world& world;

public:
    system(class world&);
    virtual ~system()     = default;
    virtual void start()  = 0;
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
