
#pragma once
#include "__common.hpp"
#include "ecs_common.hpp"
#include "entity.hpp"

#include <unordered_map>

namespace p201
{

class entity_manager
{
    public:
    std::unordered_map<id_t, std::unique_ptr<entity>> entities;

    protected:
    size_t __entityc = 0;

    public:
    entity_manager()  = default;
    ~entity_manager() = default;
    entity& new_entity(entity_type, class world&);
    void    delete_entity(id_t);
};

} // namespace p201
