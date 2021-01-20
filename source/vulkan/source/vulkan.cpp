
#include "vulkan.hpp"

#include <SDL_vulkan.h>
#include <__common.hpp>
#include <algorithm>
#include <exception>

namespace p201
{
vk::UniqueShaderModule vulkan::create_shader(const std::string& shader)
{
    auto result = spirv.CompileGlslToSpv(shader, shader_infer, "");
    if (result.GetCompilationStatus() != shader_success)
        throw std::runtime_error(result.GetErrorMessage());
    auto bytecode = std::vector<std::uint32_t>(result.cbegin(), result.cend());

    auto info = vk::ShaderModuleCreateInfo();
    info.setCodeSize(bytecode.size() * sizeof(std::uint32_t));
    info.setPCode(bytecode.data());
    return device->createShaderModuleUnique(info);
}
void vulkan::create_instance(handle_types::window* window)
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

    /** @todo Should only be enabled in debug mode. */
    result = vk::enumerateInstanceLayerProperties(&count, nullptr);
    if (result != vk::Result::eSuccess)
        throw std::runtime_error("Failed to get Vulkan layer count");
    auto __layers = std::vector<vk::LayerProperties>(count);
    result = vk::enumerateInstanceLayerProperties(&count, __layers.data());
    if (result != vk::Result::eSuccess)
        throw std::runtime_error("Failed to get Vulkan layer names");

    std::vector<const char*> layers;
    for (auto& layer : __layers) layers.emplace_back(layer.layerName.data());

    if (!SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr))
        throw std::runtime_error("Failed to get Vulkan extension count");
    auto exts = std::vector<const char*>(count);
    if (!SDL_Vulkan_GetInstanceExtensions(window, &count, exts.data()))
        throw std::runtime_error("Failed to get Vulkan extensions");

    auto info = vk::InstanceCreateInfo();
    info.setEnabledExtensionCount(exts.size());
    info.setPpEnabledExtensionNames(exts.data());
    if constexpr (__debug__)
    {
        info.setEnabledLayerCount(layers.size());
        info.setPpEnabledLayerNames(layers.data());
    }
    info.setPApplicationInfo(&app);

    instance = vk::createInstanceUnique(info);
    if (!instance) throw std::runtime_error("Failed to create Vulkan instance");
}
void vulkan::create_surface(handle_types::window* window)
{
    VkSurfaceKHR handle;
    if (!SDL_Vulkan_CreateSurface(window, *instance, &handle))
        throw std::runtime_error("Failed to get create Vulkan surface");
    surface = vk::UniqueSurfaceKHR(handle, *instance);
}
void vulkan::create_device()
{
    /** @todo Add GPU selection protocol. */
    if (!instance->enumeratePhysicalDevices().size())
        throw std::runtime_error("Failed to find a compatible Vulkan device");
    gpu = instance->enumeratePhysicalDevices().front();

    auto qf_props = gpu.getQueueFamilyProperties();
    for (std::uint32_t i = 0; i < qf_props.size(); ++i)
    {
        if (qf_props.at(i).queueFlags & vk::QueueFlagBits::eGraphics)
            graphics_index = i;
    }
    for (std::uint32_t i = 0; i < qf_props.size(); ++i)
    {
        if (gpu.getSurfaceSupportKHR(i, surface.get())) present_index = i;
    }

    if (graphics_index != present_index)
        queue_family_indices = { graphics_index, present_index };
    else
        queue_family_indices = { graphics_index };

    std::vector<vk::DeviceQueueCreateInfo> queue_infos;
    float                                  priority = 0.0f;
    for (auto& index : queue_family_indices)
    {
        auto flags = vk::DeviceQueueCreateFlags();
        auto info  = vk::DeviceQueueCreateInfo(flags, index, 1, &priority);
        queue_infos.emplace_back(info);
    }
    std::vector<const char*> ext;
    ext.emplace_back("VK_KHR_swapchain");
    ext.emplace_back("VK_KHR_portability_subset");

    auto device_info = vk::DeviceCreateInfo();
    device_info.setFlags(vk::DeviceCreateFlags());
    device_info.setQueueCreateInfoCount(queue_infos.size());
    device_info.setPQueueCreateInfos(queue_infos.data());
    device_info.setEnabledLayerCount(0);
    device_info.setPpEnabledLayerNames(nullptr);
    device_info.setEnabledExtensionCount(ext.size());
    device_info.setPpEnabledExtensionNames(ext.data());
    device = gpu.createDeviceUnique(device_info);
}
void vulkan::create_swapchain(handle_types::window* window)
{
    if constexpr (__debug__)
    {
        P201_EVAL_DISCARD(gpu.getSurfaceCapabilitiesKHR(*surface));
        P201_EVAL_DISCARD(gpu.getSurfaceFormatsKHR(*surface));
    }

    int width = 0, height = 0;
    SDL_Vulkan_GetDrawableSize(window, &width, &height);
    extent = vk::Extent2D(width, height);

    auto info = vk::SwapchainCreateInfoKHR();
    info.setSurface(surface.get());
    info.setMinImageCount(swapchain_image_count);
    info.setImageFormat(format);
    info.setImageColorSpace(vk::ColorSpaceKHR::eSrgbNonlinear);
    info.setImageExtent(extent);
    info.setImageArrayLayers(1);
    info.setImageUsage(vk::ImageUsageFlagBits::eColorAttachment);
    if (queue_family_indices.size() < 2)
    {
        info.setImageSharingMode(vk::SharingMode::eExclusive);
        info.setQueueFamilyIndexCount(0);
        info.setPQueueFamilyIndices(nullptr);
    }
    else
    {
        info.setImageSharingMode(vk::SharingMode::eConcurrent);
        info.setQueueFamilyIndexCount(queue_family_indices.size());
        info.setPQueueFamilyIndices(queue_family_indices.data());
    }
    info.setPreTransform(vk::SurfaceTransformFlagBitsKHR::eIdentity);
    info.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque);
    info.setPresentMode(vk::PresentModeKHR::eFifo);
    info.setClipped(true);
    info.setOldSwapchain(nullptr);

    swapchain = device->createSwapchainKHRUnique(info);

    auto images = device->getSwapchainImagesKHR(swapchain.get());
    for (auto& image : images)
    {
        using sw        = vk::ComponentSwizzle;
        using iafb      = vk::ImageAspectFlagBits;
        auto components = vk::ComponentMapping(sw::eR, sw::eG, sw::eB, sw::eA);
        auto isr        = vk::ImageSubresourceRange(iafb::eColor, 0, 1, 0, 1);

        auto info = vk::ImageViewCreateInfo();
        info.setFlags(vk::ImageViewCreateFlags());
        info.setImage(image);
        info.setViewType(vk::ImageViewType::e2D);
        info.setFormat(format);
        info.setComponents(components);
        info.setSubresourceRange(isr);
        image_views.emplace_back(device->createImageViewUnique(info));
    }
}
void vulkan::create_pipeline()
{
    auto v_shader = create_shader("");
    auto v_info   = vk::PipelineShaderStageCreateInfo();
    v_info.setStage(vk::ShaderStageFlagBits::eVertex);
    v_info.setModule(*v_shader);
    v_info.setPName("main");

    auto f_shader = create_shader("");
    auto f_info   = vk::PipelineShaderStageCreateInfo();
    f_info.setStage(vk::ShaderStageFlagBits::eFragment);
    f_info.setModule(*f_shader);
    f_info.setPName("main");

    auto stage_infos = std::vector<vk::PipelineShaderStageCreateInfo>();
    stage_infos.emplace_back(v_info);
    stage_infos.emplace_back(f_info);

    auto v_input_info = vk::PipelineVertexInputStateCreateInfo();
    v_input_info.setVertexBindingDescriptionCount(0);
    v_input_info.setPVertexBindingDescriptions(nullptr);
    v_input_info.setVertexAttributeDescriptionCount(0);
    v_input_info.setPVertexAttributeDescriptions(nullptr);

    auto input_asm_info = vk::PipelineInputAssemblyStateCreateInfo();
    input_asm_info.setTopology(vk::PrimitiveTopology::eTriangleList);
    input_asm_info.setPrimitiveRestartEnable(false);

    auto viewport =
        vk::Viewport(0.0f, 0.0f, extent.width, extent.height, 0.0f, 1.0f);

    auto scissor = vk::Rect2D({ 0, 0 }, extent);

    auto viewport_info = vk::PipelineViewportStateCreateInfo();
    viewport_info.setViewportCount(1);
    viewport_info.setPViewports(&viewport);
    viewport_info.setScissorCount(1);
    viewport_info.setPScissors(&scissor);

    auto raster_info = vk::PipelineRasterizationStateCreateInfo();
    raster_info.setDepthClampEnable(false);
    raster_info.setRasterizerDiscardEnable(false);
    raster_info.setPolygonMode(vk::PolygonMode::eFill);
    raster_info.setFrontFace(vk::FrontFace::eCounterClockwise);
    raster_info.setLineWidth(1.0f);

    auto multisampling_info = vk::PipelineMultisampleStateCreateInfo();
    multisampling_info.setRasterizationSamples(vk::SampleCountFlagBits::e1);
    multisampling_info.setSampleShadingEnable(false);
    multisampling_info.setMinSampleShading(1.0f);

    auto color_blend_attach = vk::PipelineColorBlendAttachmentState();
    color_blend_attach.setSrcColorBlendFactor(vk::BlendFactor::eOne);
    color_blend_attach.setDstColorBlendFactor(vk::BlendFactor::eZero);
    color_blend_attach.setColorBlendOp(vk::BlendOp::eAdd);
    color_blend_attach.setSrcAlphaBlendFactor(vk::BlendFactor::eOne);
    color_blend_attach.setDstAlphaBlendFactor(vk::BlendFactor::eZero);
    auto cwm = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
               vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
    color_blend_attach.setColorWriteMask(cwm);

    auto color_blend = vk::PipelineColorBlendStateCreateInfo();
    color_blend.setLogicOpEnable(false);
    color_blend.setLogicOp(vk::LogicOp::eCopy);
    color_blend.setAttachmentCount(1);
    color_blend.setPAttachments(&color_blend_attach);

    pipeline_layout = device->createPipelineLayoutUnique({}, nullptr);
}
} // namespace p201