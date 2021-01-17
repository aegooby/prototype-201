
#pragma once
#include <__common.hpp>
#include <filesystem>
#include <unordered_map>
#include <util.hpp>
#include <vector>

namespace p201
{

namespace assets
{
namespace sprite
{
/**
 * @brief It shames me so much to have to put this in here that I might
 *        commit suicide like a disgraced Japanese office worker but this
 *        is here for sprite loading until I find a better way.
 */
struct flipbook
{
    /** @brief Textures in the flipbook (sequential). */
    std::vector<SDL_Texture*> textures;

    flipbook() = default;
    ~flipbook();

    std::size_t frames() const;

    SDL_Texture* const& at(std::size_t i) const;
    SDL_Texture*&       at(std::size_t i);
};
class manager
{
protected:
    using flipbook_family = std::unordered_map<std::string, sprite::flipbook>;
    std::unordered_map<std::string, flipbook_family> flipbooks;
    std::filesystem::path                            flipbooks_path;

    SDL_Renderer* renderer = nullptr;

    void new_flipbook(const std::filesystem::path& path);
    void delete_flipbook(const std::string& family, const std::string& name);

public:
    manager(const std::string& flipbooks_path);
    ~manager() = default;

    void                    link(SDL_Renderer* renderer);
    void                    load();
    const sprite::flipbook& flipbook(const std::string& family,
                                     const std::string& name) const;
    SDL_Texture*            default_sprite(const std::string& family);

    manager(const manager&) = delete;
    manager(manager&&)      = delete;
    manager& operator=(const manager&) = delete;
    manager& operator=(manager&&) = delete;
};
} // namespace sprite
} // namespace assets

} // namespace p201
