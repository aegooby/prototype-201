
#pragma once
#include <__common.hpp>
#include <ecs.hpp>
#include <filesystem>
#include <physx.hpp>
#include <pugixml.hpp>

namespace p201
{
namespace serialize
{
/** @todo Phase out Boost for PugiXML. */
class xml
{
private:
    class world& world;

public:
    std::filesystem::path directory;

    xml(class world&);
    ~xml() = default;
    void load_entity(class entity&, const std::string&);
    void save_entity(class entity&, const std::string&);
};
} // namespace serialize
} // namespace p201
