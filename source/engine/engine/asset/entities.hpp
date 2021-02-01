
#pragma once
#include "../__common.hpp"
#include "../ecs.hpp"
#include "../physx.hpp"

#include <filesystem>
#include <pugixml.hpp>

namespace p201
{
namespace asset
{
namespace entities
{
class pipeline
{
private:
    class world& world;

public:
    std::filesystem::path directory;

    pipeline(class world&);
    ~pipeline() = default;
    void load_entity(class entity&, const std::string&);
    void save_entity(class entity&, const std::string&);
};
} // namespace entities
} // namespace asset
} // namespace p201
