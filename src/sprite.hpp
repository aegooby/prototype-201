
#pragma once
#include "__common.hpp"
#include "exception.hpp"
#include "util.hpp"

#include <filesystem>
#include <unordered_map>
#include <vector>

namespace p201
{

namespace sprite
{
    /**
     * @brief It shames me so much to have to put this in here that I might
     *        commit suicide like a disgraced Japanese office worker but this
     *        is here for sprite loading until I find a better way.
     */
    enum type
    {
        unknown = 0,
        player  = 1,
    };
    struct flipbook
    {
        /** @brief Textures in the flipbook (sequential). */
        std::vector<SDL_Texture*> textures;
        /** @brief Whether the animation in this flipbook can be interrupted. */
        bool interupt = false;
        /** @brief Whether or not to loop the animation. */
        bool loop = false;
        /** @brief Frame rate of animation. */
        size_t fps = 60;

        flipbook()  = default;
        ~flipbook() = default;

        std::size_t frames() const
        {
            return textures.size();
        }
    };
    class manager
    {
    protected:
        std::unordered_map<sprite::type, flipbook> flipbooks;

        SDL_Renderer*& sdl_renderer;

    public:
        manager(SDL_Renderer*& renderer) : sdl_renderer(renderer) { }
        ~manager() = default;

        flipbook& new_flipbook(sprite::type type, const std::string& directory)
        {
            flipbooks.emplace(std::make_pair(type, sprite::flipbook()));
            auto& flipbook = flipbooks.at(type);
            for (auto& entry : std::filesystem::directory_iterator(directory))
            {
                const std::string& path_str  = entry.path().string();
                const char*        path_cstr = path_str.c_str();
                SDL_Texture* texture = IMG_LoadTexture(sdl_renderer, path_cstr);
                if (!texture) throw sdl_error("Null texture");
                flipbook.textures.emplace_back(texture);
            }
            debug(std::cout << "new flipbook (\"" << directory << "\")");
            debug(std::cout << std::endl);
            return flipbook;
        }
        flipbook& flipbook(sprite::type type)
        {
            return flipbooks.at(type);
        }
        void delete_flipbook(sprite::type type)
        {
            flipbooks.erase(type);
        }

        // Preventing copying and moving
        manager(const manager&) = delete;
        manager(manager&&)      = delete;
        manager& operator=(const manager&) = delete;
        manager& operator=(manager&&) = delete;
    };
} // namespace sprite

} // namespace p201
