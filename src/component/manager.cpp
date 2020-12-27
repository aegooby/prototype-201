
#include "manager.hpp"

#include "../__common.hpp"
#include "../entity.hpp"

namespace p201
{

std::unique_ptr<struct component>& component_manager::component(entity& entity)
{
    if (!__entity_map.count(entity.id))
        throw std::runtime_error("Component not found.");
    return components.at(__entity_map.at(entity.id));
}
/** @brief Registers a component under the specified entity. */
void component_manager::add_component(
    entity& entity, std::unique_ptr<struct component>&& component)
{
    __entity_map.emplace(entity.id, components.size());
    components.emplace_back(
        std::forward<std::unique_ptr<struct component>>(component));
}
/** @brief Removes the component associated with the manager's type. */
void component_manager::remove_component(entity& entity)
{
    components.erase(components.begin() + __entity_map.at(entity.id));
    __entity_map.erase(entity.id);
}

} // namespace p201
