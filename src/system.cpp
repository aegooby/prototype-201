
#include "system.hpp"

#include "__common.hpp"
#include "entity.hpp"
#include "world.hpp"

namespace p201
{

const std::unordered_map<std::type_index, enum system::flag> system::flags = {
    { typeid(render_component), system::flag::render },
    { typeid(transform_component), system::flag::transform },
    { typeid(movement_component), system::flag::movement },
    { typeid(collision_component), system::flag::collision },
    { typeid(input_component), system::flag::input },
};

system::system(class world& world) : world(world) { }
void system::register_entity(class entity& entity)
{
    if (!__registered_entities.count(entity.id))
        __registered_entities.emplace(entity.id, entity);
}
void system::deregister_entity(class entity& entity)
{
    __registered_entities.erase(entity.id);
}

} // namespace p201
