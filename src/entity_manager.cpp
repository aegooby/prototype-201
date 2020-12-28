
#include "entity_manager.hpp"

#include "__common.hpp"
#include "entity.hpp"
#include "world.hpp"

namespace p201
{

entity& entity_manager::new_entity(class world& world)
{
    entities.emplace(__entityc, std::make_unique<entity>(__entityc, world));
    auto __entityc_temp = __entityc;
    ++__entityc;
    return *entities.at(__entityc_temp);
}
void entity_manager::delete_entity(id_t id)
{
    entities.erase(id);
}
std::size_t entity_manager::entityc() const
{
    return __entityc;
}

} // namespace p201
