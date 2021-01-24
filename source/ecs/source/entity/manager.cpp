
#include "manager.hpp"

#include "entity.hpp"

#include <__common.hpp>
#include <core.hpp>

namespace p201
{
namespace entities
{
entity& manager::new_entity(class world& world)
{
    entities.emplace(__entityc, std::make_unique<entity>(__entityc, world));
    auto __entityc_temp = __entityc;
    ++__entityc;
    return *entities.at(__entityc_temp);
}
void manager::delete_entity(entity::id_t id)
{
    entities.erase(id);
}
std::size_t manager::entityc() const
{
    return __entityc;
}
} // namespace entities
} // namespace p201
