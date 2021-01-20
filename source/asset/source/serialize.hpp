
#pragma once
#include <__common.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <ecs.hpp>
#include <filesystem>
#include <physx.hpp>

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
    void load_entity(class entity& entity, const std::string& name);
    void save_entity(class entity& entity, const std::string& name)
    {
        std::filesystem::path filepath = (directory / name).concat(".xml");
        boost::property_tree::ptree ptree;
        ptree.put("entity.name", name);
        ptree.put("entity.components", "");

        for (std::size_t i = 0; i < entity.flag.size(); ++i)
        {
            if (!entity.flag.test(i)) continue;
            auto& component = ptree.add("entity.components.component", "");
            component.add("flag", i);
            switch (i)
            {
                default:
                    break;
            }
        }

        boost::property_tree::write_xml(filepath.string(), ptree);
    }
};
} // namespace serialize
} // namespace p201
