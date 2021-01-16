
#pragma once
#include "../../__common.hpp"
#include "../../ecs.hpp"

namespace p201
{
namespace components
{
struct transform : public component
{
    using __base  = component;
    using manager = component_manager_template<components::transform>;

    static constexpr std::size_t flag = 2;

    /** @brief Previous coordinate used to interpolate in updates. */
    vector_3 lerp = vector_3(0.0f, 0.0f, 0.0f);
    /** @brief Game coordinate position (not isometric position). */
    vector_3 position = vector_3(0.0f, 0.0f, 0.0f);
    /** @brief Direction the entity is facing (not always used). */
    enum
    {
        north      = 1,
        south      = 2,
        east       = 3,
        west       = 4,
        north_east = 5,
        north_west = 6,
        south_east = 7,
        south_west = 8,
    } direction = north;

    transform(std::size_t entity) : __base(entity) { }
    virtual ~transform() override = default;
};
} // namespace components
} // namespace p201