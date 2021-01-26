
#pragma once
#include "../media-layer.hpp"
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
struct flipbook
{
    /** @brief Textures in the flipbook (sequential). */
    std::vector<SDL_Texture*> textures;

    flipbook() = default;
    ~flipbook();

    std::size_t frames() const;

    handle_types::texture* const& at(std::size_t i) const;
    handle_types::texture*&       at(std::size_t i);
};
class pipeline
{
protected:
    using flipbook_family = std::unordered_map<std::string, struct flipbook>;
    std::unordered_map<std::string, flipbook_family> flipbooks;
    std::filesystem::path                            flipbooks_path;

    handle_types::renderer* renderer = nullptr;

    void new_flipbook(const std::filesystem::path& path);
    void delete_flipbook(const std::string& family, const std::string& name);

public:
    pipeline(const std::string& flipbooks_path);
    ~pipeline() = default;

    void                   link(handle_types::renderer* renderer);
    void                   load();
    const struct flipbook& flipbook(const std::string& family,
                                    const std::string& name) const;
    SDL_Texture*           default_sprite(const std::string& family);

    pipeline(const pipeline&) = delete;
    pipeline(pipeline&&)      = delete;
    pipeline& operator=(const pipeline&) = delete;
    pipeline& operator=(pipeline&&) = delete;
};
} // namespace textures
} // namespace asset

} // namespace p201
