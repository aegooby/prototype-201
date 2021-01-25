
#pragma once
#include "entity.hpp"

#include <__common.hpp>
#include <unordered_map>

namespace p201
{
namespace entities
{
/** @brief The entity manager manages entities it's in the fucking name. */
class manager
{
public:
    std::unordered_map<entity::id_t, std::unique_ptr<entity>> entities;

protected:
    std::size_t __entityc = 0;

public:
    manager()  = default;
    ~manager() = default;
    entity&     new_entity(class world&);
    void        delete_entity(std::size_t);
    std::size_t entityc() const;
};
} // namespace entities
} // namespace p201
