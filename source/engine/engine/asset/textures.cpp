
#include "textures.hpp"

#include "../util.hpp"

#include <__common.hpp>
#include <filesystem>
#include <unordered_map>
#include <vector>

namespace p201
{

namespace asset
{
namespace textures
{
flipbook::~flipbook()
{
    for (auto& texture : textures) SDL_DestroyTexture(texture);
}
std::size_t flipbook::frames() const
{
    return textures.size();
}
SDL_Texture* const& flipbook::at(std::size_t i) const
{
    return textures.at(i);
}
SDL_Texture*& flipbook::at(std::size_t i)
{
    return textures.at(i);
}

void pipeline::new_flipbook(const std::filesystem::path& path)
{
    if (!std::filesystem::is_directory(path)) return;
    const auto& name   = path.filename();
    const auto& family = path.parent_path().filename();
    flipbooks.try_emplace(family, flipbook_family());
    flipbooks.at(family).emplace(name, textures::flipbook());
    auto& flipbook = flipbooks.at(family).at(name);

    std::vector<std::string> sprite_paths;
    for (auto& entry : std::filesystem::directory_iterator(path))
        sprite_paths.emplace_back(entry.path().string());

    std::sort(sprite_paths.begin(), sprite_paths.end());
    for (auto& sprite_path : sprite_paths)
    {
        auto texture = IMG_LoadTexture(renderer, sprite_path.c_str());
        if (texture) flipbook.textures.emplace_back(texture);
    }
}
void pipeline::delete_flipbook(const std::string& family,
                               const std::string& name)
{
    flipbooks.at(family).erase(name);
}

pipeline::pipeline(const std::string& flipbooks_path)
    : flipbooks_path(flipbooks_path)
{ }
void pipeline::link(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}
void pipeline::load()
{
    for (auto& family : std::filesystem::directory_iterator(flipbooks_path))
    {
        const auto& path = family.path();
        if (!std::filesystem::is_directory(path)) continue;
        for (auto& name : std::filesystem::directory_iterator(path))
            new_flipbook(name.path());
    }
}
const struct flipbook& pipeline::flipbook(const std::string& family,
                                          const std::string& name) const
{
    return flipbooks.at(family).at(name);
}
SDL_Texture* pipeline::default_sprite(const std::string& family)
{
    return flipbook(family, "default").at(0);
}
} // namespace textures
} // namespace asset

} // namespace p201
