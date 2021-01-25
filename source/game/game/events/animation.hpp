
#pragma once
#include <engine/ecs.hpp>
#include <engine/event.hpp>

namespace p201
{
namespace events
{
class animation : public event
{
public:
    class entity& entity;
    std::string   name;

    animation(class entity& entity, const std::string& name)
        : entity(entity), name(name)
    { }
    virtual ~animation() override = default;
};
} // namespace events
}