
#pragma once
#include "../../__common.hpp"
#include "../../ecs.hpp"

namespace p201
{
namespace components
{
struct animation : public component
{
    using __base    = component;
    using manager = component_manager_template<components::animation>;

    static constexpr std::size_t flag = 6;

    std::string name      = "default";
    std::size_t frame     = 0;
    std::size_t index     = 0;
    float       fps       = 0.0f;
    bool        interrupt = false;
    bool        loop      = true;

    animation(std::size_t entity) : __base(entity) { }
    virtual ~animation() override = default;
};
} // namespace components
} // namespace p201