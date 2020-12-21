
#include "component.hpp"

#include "__common.hpp"
#include "entity.hpp"
#include "event.hpp"
#include "input.hpp"
#include "render_system.hpp"
#include "sprite.hpp"

namespace p201
{

component::~component() = default;

void render_component::add_flipbook(const std::string&, float fps,
                                    const sprite_info& info)
{
    //  flipbooks.emplace
}
void render_component::remove_flipbook(const std::string& str)
{
    flipbooks.erase(str);
}

} // namespace p201
