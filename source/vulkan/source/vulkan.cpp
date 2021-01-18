
#include "vulkan.hpp"

#include <SDL_vulkan.h>
#include <__common.hpp>
#include <algorithm>
#include <exception>

namespace p201
{
void vulkan::create_instance(SDL_Window* window)
{
    vk::ApplicationInfo app = vk::ApplicationInfo();
    app.setPNext(nullptr);
    app.setPApplicationName("Prototype 201");
    app.setApplicationVersion(0);
    app.setPEngineName("Prototype 201");
    app.setEngineVersion(0);
    app.setApiVersion(VK_API_VERSION_1_2);

    std::uint32_t count  = 0;
    vk::Result    result = vk::Result::eSuccess;

    result = vk::enumerateInstanceLayerProperties(&count, nullptr);
    if (result != vk::Result::eSuccess)
        throw std::runtime_error("Failed to get Vulkan layer count");
    std::vector<vk::LayerProperties> layers(count);
    result = vk::enumerateInstanceLayerProperties(&count, layers.data());
    if (result != vk::Result::eSuccess)
        throw std::runtime_error("Failed to get Vulkan layer names");

    std::vector<const char*> layer_names;
    for (auto& layer : layers) layer_names.emplace_back(layer.layerName.data());

    if (!SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr))
        throw std::runtime_error("Failed to get Vulkan extension count");
    std::vector<const char*> ext_names(count);
    if (!SDL_Vulkan_GetInstanceExtensions(window, &count, ext_names.data()))
        throw std::runtime_error("Failed to get Vulkan extensions");

    vk::InstanceCreateInfo info = vk::InstanceCreateInfo();
    info.setEnabledExtensionCount(ext_names.size());
    info.setPpEnabledExtensionNames(ext_names.data());
    info.setEnabledLayerCount(layer_names.size());
    info.setPpEnabledLayerNames(layer_names.data());
    info.setPApplicationInfo(&app);

    instance = vk::createInstanceUnique(info);
    if (!instance) throw std::runtime_error("Failed to create Vulkan instance");
}
void vulkan::create_surface(SDL_Window* window)
{
    VkSurfaceKHR handle;
    if (!SDL_Vulkan_CreateSurface(window, *instance, &handle))
        throw std::runtime_error("Failed to get create Vulkan surface");
    surface = vk::UniqueSurfaceKHR(handle, *instance);
}
void vulkan::select_gpu()
{
    gpu = instance->enumeratePhysicalDevices().front();

    auto qf_props = gpu.getQueueFamilyProperties();

    std::size_t graphics_index = 0;
    for (std::size_t i = 0; i < qf_prop.size(); ++i)
    {
        if (qf_props.at(i).queueFlags & vk::QueueFlagBits::eGraphics)
            graphics_index = i;
    }

    std::size_t present_index = 0;
    for (std::uint32_t i = 0; i < qf_prop.size(); ++i)
    {
        if (gpu.getSurfaceSupportKHR(i, surface.get()))
            present_index = std::size_t(i);
    }
}
} // namespace p201