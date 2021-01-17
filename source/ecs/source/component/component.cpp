
#include "component.hpp"

namespace p201
{
component::component(std::size_t entity) : entity(entity) { }
component::~component() = default;
} // namespace p201
