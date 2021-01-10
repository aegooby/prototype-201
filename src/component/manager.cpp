
#include "manager.hpp"

#include "../__common.hpp"
#include "../entity.hpp"

namespace p201
{

std::unique_ptr<struct component>& component_manager::component(std::size_t id)
{
    if (!__entity_map.count(id))
        throw std::runtime_error("Component not found.");
    return components.at(__entity_map.at(id));
}
/** @brief Registers a component under the specified entity. */
void component_manager::add_component(
    std::size_t id, std::unique_ptr<struct component>&& component)
{
    __entity_map.emplace(id, components.size());
    components.emplace_back(
        std::forward<std::unique_ptr<struct component>>(component));
}
/** @brief Removes the component associated with the manager's type. */
void component_manager::remove_component(std::size_t id)
{
    components.erase(components.begin() + __entity_map.at(id));
    __entity_map.erase(id);
}

} // namespace p201
