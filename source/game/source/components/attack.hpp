
#pragma once
#include "character.hpp"

#include <__common.hpp>
#include <ecs.hpp>

namespace p201
{
namespace components
{
struct attack : public component
{
    using __base  = component;
    using manager = component_manager_template<components::attack>;

    static constexpr std::size_t flag = 9;

    px::shape* shape = nullptr;

    attack(entity::id_t entity) : __base(entity) { }
    virtual ~attack() override = default;
};
} // namespace components
} // namespace p201