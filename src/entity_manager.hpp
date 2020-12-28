
#pragma once
#include "__common.hpp"
#include "entity.hpp"

#include <unordered_map>

namespace p201
{

/** @brief The entity manager manages entities it's in the fucking name. */
class entity_manager
{
public:
    std::unordered_map<id_t, std::unique_ptr<entity>> entities;

protected:
    std::size_t __entityc = 0;

public:
    entity_manager()  = default;
    ~entity_manager() = default;
    entity&     new_entity(class world&);
    void        delete_entity(id_t);
    std::size_t entityc() const;
};

} // namespace p201
