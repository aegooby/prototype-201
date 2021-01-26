
#include "entities.hpp"

#include "../core.hpp"

#include <__common.hpp>

namespace p201
{
namespace asset
{
namespace entities
{
pipeline::pipeline(class world& world) : world(world) { }
/** @todo This shit. */
void pipeline::load_entity(class entity& entity, const std::string& name)
{
    P201_EVAL_DISCARD(entity);
    P201_EVAL_DISCARD(name);
    std::filesystem::path filepath = (directory / name).concat(".xml");
    pugi::xml_document    document;
    document.load_file(filepath.string());
}
} // namespace entities
} // namespace asset
} // namespace p201
