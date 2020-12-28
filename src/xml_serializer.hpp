
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
    void load_entity(class entity& entity, const std::string& name)
    {
        std::filesystem::path filepath = (directory / name).concat(".xml");
        boost::property_tree::ptree ptree;
        boost::property_tree::read_xml(filepath.string(), ptree);

        for (auto& component_pair : ptree.get_child("entity.components"))
        {
            const auto& component = component_pair.second;
            const auto& flag =
                component::flag(component.get<std::size_t>("flag"));
            switch (flag)
            {
                case component::flag::render:
                {
                    auto& render  = entity.add_component<components::render>();
                    render.family = component.get<std::string>("family");
                    render.rect.w = component.get<std::size_t>("rect.w");
                    render.rect.h = component.get<std::size_t>("rect.h");
                    break;
                }
                case component::flag::transform:
                {
                    auto& transform =
                        entity.add_component<components::transform>();
                    transform.position.x() = component.get<float>("position.x");
                    transform.position.y() = component.get<float>("position.y");
                    transform.position.z() = component.get<float>("position.z");
                    break;
                }
                case component::flag::movement:
                {
                    auto& movement =
                        entity.add_component<components::movement>();
                    movement.velocity.x() = component.get<float>("velocity.x");
                    movement.velocity.y() = component.get<float>("velocity.y");
                    movement.velocity.z() = component.get<float>("velocity.z");
                    movement.accel.x()    = component.get<float>("accel.x");
                    movement.accel.y()    = component.get<float>("accel.y");
                    movement.accel.z()    = component.get<float>("accel.z");
                    break;
                }
                case component::flag::collision:
                {
                    auto& collision =
                        entity.add_component<components::collision>();
                    (void)collision;
                    break;
                }
                case component::flag::input:
                {
                    auto& input = entity.add_component<components::input>();
                    (void)input;
                    break;
                }
                case component::flag::animation:
                {
                    auto& animation =
                        entity.add_component<components::animation>();
                    (void)animation;
                    break;
                }
                default:
                    break;
            }
        }
    }
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
                case component::flag::render:
                {
                    auto& render = entity.component<components::render>();
                    component.add("family", render.family);
                    component.add("rect.w", render.rect.w);
                    component.add("rect.h", render.rect.h);
                    break;
                }
                case component::flag::transform:
                {
                    auto& transform = entity.component<components::transform>();
                    component.add("position.x", transform.position.x());
                    component.add("position.y", transform.position.y());
                    component.add("position.z", transform.position.z());
                    break;
                }
                case component::flag::movement:
                {
                    break;
                }
                case component::flag::collision:
                {
                    break;
                }
                case component::flag::input:
                {
                    break;
                }
                case component::flag::animation:
                {
                    break;
                }
                default:
                    break;
            }
        }

        boost::property_tree::write_xml(filepath.string(), ptree);
    }
};

} // namespace p201
