
#pragma once
#include <__common.hpp>
#include <vulkan/vulkan.hpp>

namespace p201
{
class vulkan
{
public:
    vk::UniqueInstance   instance;
    vk::UniqueSurfaceKHR surface;
    vk::PhysicalDevice   gpu = nullptr;
    vk::UniqueDevice     device;

    vulkan()  = default;
    ~vulkan() = default;
    void create_instance(SDL_Window*);
    void create_surface(SDL_Window*);
    void select_gpu();
};
} // namespace p201