
#pragma once
#include "__common.hpp"
#include "component.hpp"
#include "entity.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <filesystem>

namespace p201
{

class xml_serializer
{
public:
    std::filesystem::path directory;

    xml_serializer()  = default;
    ~xml_serializer() = default;
    void load_entity(const std::string& name, class entity& entity)
    {
        std::filesystem::path filepath = (directory / name).concat(".xml");
        boost::property_tree::ptree ptree;
        boost::property_tree::read_xml(filepath.string(), ptree);

        for (auto& component_pair : ptree.get_child("entity.components"))
        {
            const auto& component = component_pair.second;
            const auto& flag = component::flag(component.get<size_t>("flag"));
            switch (flag)
            {
                case component::flag::render:
                {
                    auto& render  = entity.add_component<render_component>();
                    render.rect.w = component.get<size_t>("rect.w");
                    render.rect.h = component.get<size_t>("rect.h");
                    break;
                }
                case component::flag::transform:
                {
                    auto& transform =
                        entity.add_component<transform_component>();
                    transform.position.x = component.get<size_t>("position.x");
                    transform.position.y = component.get<size_t>("position.y");
                    transform.position.z = component.get<size_t>("position.z");
                    break;
                }
                case component::flag::movement:
                {
                    auto& movement = entity.add_component<movement_component>();
                    (void)movement;
                    break;
                }
                case component::flag::collision:
                {
                    auto& collision =
                        entity.add_component<collision_component>();
                    (void)collision;
                    break;
                }
                case component::flag::input:
                {
                    auto& input = entity.add_component<input_component>();
                    (void)input;
                    break;
                }
                default:
                    break;
            }
        }
    }
    void save_entity(const std::string& name, class entity& entity)
    {
        std::filesystem::path filepath = (directory / name).concat(".xml");
        boost::property_tree::ptree ptree;
        ptree.put("entity.name", name);

        boost::property_tree::write_xml(filepath.string(), ptree);
    }
};

} // namespace p201
