
#pragma once
#include "../../__common.hpp"
#include "../../ecs.hpp"

namespace p201
{
namespace components
{
struct camera_focus : public component
{
    using __base  = component;
    using manager = component_manager_template<components::camera_focus>;

    static constexpr std::size_t flag = 7;

    camera_focus(std::size_t entity) : __base(entity) { }
    virtual ~camera_focus() override = default;
};
} // namespace components
} // namespace p201