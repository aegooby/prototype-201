
#include "vulkan.hpp"

#include <SDL_vulkan.h>
#include <__common.hpp>
#include <exception>

namespace p201
{
vk::Instance   vulkan::instance = nullptr;
vk::SurfaceKHR vulkan::surface  = nullptr;
void           vulkan::create_instance(SDL_Window* window)
{
    std::uint32_t count = 0;
    if (!SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr))
        throw std::runtime_error("Failed to get Vulkan extension count");
    std::vector<const char*> names = std::vector<const char*>(count);
    if (!SDL_Vulkan_GetInstanceExtensions(window, &count, names.data()))
        throw std::runtime_error("Failed to get Vulkan extensions");
    vk::InstanceCreateInfo info  = {};
    info.enabledExtensionCount   = names.size();
    info.ppEnabledExtensionNames = names.data();

    auto result = vk::createInstance(&info, nullptr, &instance);
}
void vulkan::create_surface(SDL_Window* window)
{
    auto handle = VkSurfaceKHR(surface);
    if (!SDL_Vulkan_CreateSurface(window, instance, &handle))
        throw std::runtime_error("Failed to get create Vulkan surface");
}
} // namespace p201