
#pragma once
#include <__common.hpp>
#include <vulkan/vulkan.hpp>

namespace p201
{
class vulkan
{
public:
    static vk::Instance   instance;
    static vk::SurfaceKHR surface;

    vulkan()  = default;
    ~vulkan() = default;
    static void create_instance(SDL_Window*);
    static void create_surface(SDL_Window*);
};
} // namespace p201