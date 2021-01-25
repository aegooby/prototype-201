
#include "component.hpp"

namespace p201
{
component::component(entity::id_t entity) : entity(entity) { }
component::~component() = default;
} // namespace p201
