
#include "system.hpp"

#include <__common.hpp>
#include <util.hpp>

namespace p201
{

system::~system() = default;

void system::register_entity(std::size_t id)
{
    if (!__registered_entities.count(id)) __registered_entities.emplace(id);
}
void system::deregister_entity(std::size_t id)
{
    __registered_entities.erase(id);
}

void system::start() { }
void system::update([[maybe_unused]] float dt) { }

} // namespace p201
