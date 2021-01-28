
#include "graphics-api.hpp"

#include "../core.hpp"

#include <SDL2/SDL_vulkan.h>
#include <__common.hpp>
#include <algorithm>
#include <exception>
#include <fstream>

namespace p201
{
vulkan::vulkan(class window& window) : window(window) { }

vk::ShaderModuleCreateInfo
vulkan::create_shader(const std::string& shader, shader_kind kind,
                      std::vector<std::uint32_t>& bytecode)
{
    auto result = spirv.CompileGlslToSpv(shader, kind, "");
    if (result.GetCompilationStatus() != shader_success)
        throw std::runtime_error(result.GetErrorMessage());
    bytecode = std::vector<std::uint32_t>(result.cbegin(), result.cend());

    auto info = vk::ShaderModuleCreateInfo();
    info.setCodeSize(bytecode.size() * sizeof(std::uint32_t));
    info.setPCode(bytecode.data());
    return info;
}
void vulkan::create_instance()
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
    for (auto& layer : __layers)
    {
        auto& name = layer.layerName;
        auto  size = layer.layerName.size();
        if (!std::strncmp(name.data(), "VK_LAYER_KHRONOS_validation", size))
            layers.emplace_back("VK_LAYER_KHRONOS_validation");
    }

    if (!SDL_Vulkan_GetInstanceExtensions(window.handle, &count, nullptr))
        throw std::runtime_error("Failed to get Vulkan extension count");
    auto exts = std::vector<const char*>(count);
    if (!SDL_Vulkan_GetInstanceExtensions(window.handle, &count, exts.data()))
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
void vulkan::create_surface()
{
    VkSurfaceKHR handle = nullptr;
    if (!SDL_Vulkan_CreateSurface(window.handle, *instance, &handle))
        throw std::runtime_error("Failed to create Vulkan surface");
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
    static float                           priority = 0.0f;
    for (auto& index : queue_family_indices)
    {
        auto flags = vk::DeviceQueueCreateFlags();
        auto info  = vk::DeviceQueueCreateInfo(flags, index, 1, &priority);
        queue_infos.emplace_back(info);
    }
    std::vector<const char*> ext;
    for (auto& prop : gpu.enumerateDeviceExtensionProperties())
    {
        auto& name = prop.extensionName;
        auto  size = name.size();
        if (!std::strncmp(name.data(), "VK_KHR_swapchain", size))
            ext.emplace_back("VK_KHR_swapchain");
        /** @todo Doesn't work. */
        // if (!std::strncmp(name.data(), "VK_KHR_portability_subset", size))
        //     ext.emplace_back("VK_KHR_portability_subset");
    }

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
void vulkan::create_swapchain()
{
    if constexpr (__debug__)
    {
        P201_EVAL_DISCARD(gpu.getSurfaceCapabilitiesKHR(*surface));
        P201_EVAL_DISCARD(gpu.getSurfaceFormatsKHR(*surface));
    }

    auto info = vk::SwapchainCreateInfoKHR();
    info.setSurface(surface.get());
    info.setMinImageCount(swapchain_image_count);
    info.setImageFormat(format);
    info.setImageColorSpace(vk::ColorSpaceKHR::eSrgbNonlinear);
    info.setImageExtent(extent);
    info.setImageArrayLayers(1);
    info.setImageUsage(vk::ImageUsageFlagBits::eColorAttachment);
    if (graphics_index != present_index)
    {
        info.setImageSharingMode(vk::SharingMode::eConcurrent);
        info.setQueueFamilyIndexCount(queue_family_indices.size());
        info.setPQueueFamilyIndices(queue_family_indices.data());
    }
    else
    {
        info.setImageSharingMode(vk::SharingMode::eExclusive);
        info.setQueueFamilyIndexCount(0);
        info.setPQueueFamilyIndices(nullptr);
    }
    info.setPreTransform(vk::SurfaceTransformFlagBitsKHR::eIdentity);
    info.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque);
    info.setPresentMode(vk::PresentModeKHR::eFifo);
    info.setClipped(true);
    info.setOldSwapchain(nullptr);

    swapchain = device->createSwapchainKHRUnique(info);

    auto images = device->getSwapchainImagesKHR(swapchain.get());
    image_views.clear();
    for (auto& image : images)
    {
        using sw        = vk::ComponentSwizzle;
        using iafb      = vk::ImageAspectFlagBits;
        auto components = vk::ComponentMapping(sw::eIdentity, sw::eIdentity,
                                               sw::eIdentity, sw::eIdentity);
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
    auto v_file   = std::fstream("assets/shaders/shader.vert");
    auto v_stream = std::stringstream();
    v_stream << v_file.rdbuf();
    std::vector<std::uint32_t> v_bytecode;
    auto v_info   = create_shader(v_stream.str(), shader_vertex, v_bytecode);
    auto v_shader = device->createShaderModuleUnique(v_info);
    auto v_stage_info = vk::PipelineShaderStageCreateInfo();
    v_stage_info.setStage(vk::ShaderStageFlagBits::eVertex);
    v_stage_info.setModule(*v_shader);
    v_stage_info.setPName("main");

    auto f_file   = std::fstream("assets/shaders/shader.frag");
    auto f_stream = std::stringstream();
    f_stream << f_file.rdbuf();
    std::vector<std::uint32_t> f_bytecode;
    auto f_info   = create_shader(f_stream.str(), shader_fragment, f_bytecode);
    auto f_shader = device->createShaderModuleUnique(f_info);
    auto f_stage_info = vk::PipelineShaderStageCreateInfo();
    f_stage_info.setStage(vk::ShaderStageFlagBits::eFragment);
    f_stage_info.setModule(*f_shader);
    f_stage_info.setPName("main");

    auto stage_infos = std::vector<vk::PipelineShaderStageCreateInfo>();
    stage_infos.emplace_back(v_stage_info);
    stage_infos.emplace_back(f_stage_info);

    auto binding_desc = vertex::binding_desc();
    auto attr_desc    = vertex::attr_desc();
    auto v_input_info = vk::PipelineVertexInputStateCreateInfo();
    v_input_info.setVertexBindingDescriptionCount(1);
    v_input_info.setPVertexBindingDescriptions(&binding_desc);
    v_input_info.setVertexAttributeDescriptionCount(attr_desc.size());
    v_input_info.setPVertexAttributeDescriptions(attr_desc.data());

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

    auto color_attachment = vk::AttachmentDescription();
    color_attachment.setFormat(format);
    color_attachment.setSamples(vk::SampleCountFlagBits::e1);
    color_attachment.setLoadOp(vk::AttachmentLoadOp::eClear);
    color_attachment.setStoreOp(vk::AttachmentStoreOp::eStore);
    color_attachment.setFinalLayout(vk::ImageLayout::ePresentSrcKHR);

    auto color_attachment_ref = vk::AttachmentReference();
    color_attachment_ref.setAttachment(0);
    color_attachment_ref.setLayout(vk::ImageLayout::eColorAttachmentOptimal);

    auto subpass = vk::SubpassDescription();
    subpass.setPipelineBindPoint(vk::PipelineBindPoint::eGraphics);
    subpass.setInputAttachmentCount(0);
    subpass.setPInputAttachments(nullptr);
    subpass.setColorAttachmentCount(1);
    subpass.setPColorAttachments(&color_attachment_ref);

    auto semaphore_info = vk::SemaphoreCreateInfo();
    image_available     = device->createSemaphoreUnique(semaphore_info);
    render_finished     = device->createSemaphoreUnique(semaphore_info);

    auto subpass_dependency = vk::SubpassDependency();
    subpass_dependency.setSrcSubpass(VK_SUBPASS_EXTERNAL);
    subpass_dependency.setDstSubpass(0);
    auto stage_mask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    subpass_dependency.setSrcStageMask(stage_mask);
    subpass_dependency.setDstStageMask(stage_mask);
    auto access_mask = vk::AccessFlagBits::eColorAttachmentRead |
                       vk::AccessFlagBits::eColorAttachmentWrite;
    subpass_dependency.setDstAccessMask(access_mask);

    auto render_pass_info = vk::RenderPassCreateInfo();
    render_pass_info.setAttachmentCount(1);
    render_pass_info.setPAttachments(&color_attachment);
    render_pass_info.setSubpassCount(1);
    render_pass_info.setPSubpasses(&subpass);
    render_pass_info.setDependencyCount(1);
    render_pass_info.setPDependencies(&subpass_dependency);

    render_pass = device->createRenderPassUnique(render_pass_info);

    auto pipeline_info = vk::GraphicsPipelineCreateInfo();
    pipeline_info.setStageCount(2);
    pipeline_info.setPStages(stage_infos.data());
    pipeline_info.setPVertexInputState(&v_input_info);
    pipeline_info.setPInputAssemblyState(&input_asm_info);
    pipeline_info.setPTessellationState(nullptr);
    pipeline_info.setPViewportState(&viewport_info);
    pipeline_info.setPRasterizationState(&raster_info);
    pipeline_info.setPMultisampleState(&multisampling_info);
    pipeline_info.setPDepthStencilState(nullptr);
    pipeline_info.setPColorBlendState(&color_blend);
    pipeline_info.setPDynamicState(nullptr);
    pipeline_info.setLayout(*pipeline_layout);
    pipeline_info.setRenderPass(*render_pass);

    pipeline = device->createGraphicsPipelineUnique({}, pipeline_info).value;
}
void vulkan::create_framebuffers()
{
    framebuffers.clear();
    for (std::size_t i = 0; i < image_views.size(); ++i)
    {
        auto info = vk::FramebufferCreateInfo();
        info.setRenderPass(*render_pass);
        info.setAttachmentCount(1);
        info.setPAttachments(&image_views.at(i).get());
        info.setWidth(extent.width);
        info.setHeight(extent.height);
        info.setLayers(1);
        framebuffers.emplace_back(device->createFramebufferUnique(info));
    }
}
void vulkan::create_command_pool()
{
    auto info = vk::CommandPoolCreateInfo();
    info.setQueueFamilyIndex(graphics_index);
    command_pool = device->createCommandPoolUnique(info);
}
void vulkan::create_vertex_buffer()
{
    /** @todo Temp values. */
    std::vector<vertex> vertices;
    vertices.emplace_back(vector_2(0.0f, -0.5f), vector_3(1.0f, 1.0f, 1.0f));
    vertices.emplace_back(vector_2(0.5f, 0.5f), vector_3(0.0f, 1.0f, 0.0f));
    vertices.emplace_back(vector_2(-0.5f, 0.5f), vector_3(0.0f, 0.0f, 1.0f));

    auto buffer_info = vk::BufferCreateInfo();
    buffer_info.setSize(sizeof(vertex) * vertices.size());
    buffer_info.setUsage(vk::BufferUsageFlagBits::eVertexBuffer);
    buffer_info.setSharingMode(vk::SharingMode::eExclusive);

    vertex_buffer = device->createBufferUnique(buffer_info);

    auto memory_reqs = device->getBufferMemoryRequirements(vertex_buffer.get());
    const auto& memory_properties = gpu.getMemoryProperties();
    auto        bits              = memory_reqs.memoryTypeBits;

    auto mask = vk::MemoryPropertyFlagBits::eHostVisible |
                vk::MemoryPropertyFlagBits::eHostCoherent;
    std::uint32_t index = ~0u;
    for (std::uint32_t i = 0; i < memory_properties.memoryTypeCount; ++i)
    {
        if ((bits & 1) && ((memory_properties.memoryTypes.at(i).propertyFlags &
                            mask) == mask))
        {
            index = i;
            break;
        }
        bits >>= 1;
    }
    assert(index != ~0u);

    auto memory_info = vk::MemoryAllocateInfo();
    memory_info.setAllocationSize(memory_reqs.size);
    memory_info.setMemoryTypeIndex(index);
    device_memory = device->allocateMemoryUnique(memory_info);

    auto __data = device->mapMemory(device_memory.get(), 0, memory_reqs.size);
    std::uint8_t* data = static_cast<std::uint8_t*>(__data);

    std::memcpy(data, vertices.data(), sizeof(vertex) * vertices.size());
    device->unmapMemory(device_memory.get());

    device->bindBufferMemory(vertex_buffer.get(), device_memory.get(), 0);
}
void vulkan::create_command_buffers()
{
    auto info = vk::CommandBufferAllocateInfo();
    info.setCommandPool(command_pool.get());
    info.setLevel(vk::CommandBufferLevel::ePrimary);
    info.setCommandBufferCount(framebuffers.size());
    command_buffers = device->allocateCommandBuffersUnique(info);

    device_queue  = device->getQueue(graphics_index, 0);
    present_queue = device->getQueue(present_index, 0);

    for (size_t i = 0; i < command_buffers.size(); i++)
    {
        auto begin_info = vk::CommandBufferBeginInfo();
        command_buffers.at(i)->begin(begin_info);
        auto clear_values     = vk::ClearValue();
        auto render_pass_info = vk::RenderPassBeginInfo();
        render_pass_info.setRenderPass(render_pass.get());
        render_pass_info.setFramebuffer(framebuffers.at(i).get());
        render_pass_info.setRenderArea(vk::Rect2D({ 0, 0 }, extent));
        render_pass_info.setClearValueCount(1);
        render_pass_info.setPClearValues(&clear_values);

        command_buffers.at(i)->beginRenderPass(render_pass_info,
                                               vk::SubpassContents::eInline);
        command_buffers.at(i)->bindVertexBuffers(0, *vertex_buffer, { 0 });
        command_buffers.at(i)->bindPipeline(vk::PipelineBindPoint::eGraphics,
                                            *pipeline);
        command_buffers.at(i)->draw(3, 1, 0, 0);
        command_buffers.at(i)->endRenderPass();
        command_buffers.at(i)->end();
    }
}
void vulkan::start()
{
    create_instance();
    create_surface();
    query_extent();
    create_device();
    create_swapchain();
    create_pipeline();
    create_framebuffers();
    create_command_pool();
    create_vertex_buffer();
    create_command_buffers();
}
void vulkan::draw()
{
    auto timeout = std::numeric_limits<uint64_t>::max();

    auto index = device->acquireNextImageKHR(swapchain.get(), timeout,
                                             image_available.get(), {});

    switch (index.result)
    {
        case vk::Result::eErrorOutOfDateKHR:
        {
            create_swapchain();
            create_pipeline();
            create_framebuffers();
            create_command_buffers();
            break;
        }
        case vk::Result::eSuccess:
            break;
        case vk::Result::eSuboptimalKHR:
            break;
        default:
            throw std::runtime_error("Failed to acquire Vulkan image");
            break;
    }

    vk::PipelineStageFlags mask =
        vk::PipelineStageFlagBits::eColorAttachmentOutput;

    auto submit_info = vk::SubmitInfo();
    submit_info.setWaitSemaphoreCount(1);
    submit_info.setPWaitSemaphores(&image_available.get());
    submit_info.setPWaitDstStageMask(&mask);
    submit_info.setCommandBufferCount(1);
    submit_info.setPCommandBuffers(&command_buffers.at(index.value).get());
    submit_info.setSignalSemaphoreCount(1);
    submit_info.setPSignalSemaphores(&render_finished.get());

    device_queue.submit(submit_info, {});

    auto present_info = vk::PresentInfoKHR();
    present_info.setWaitSemaphoreCount(1);
    present_info.setPWaitSemaphores(&render_finished.get());
    present_info.setSwapchainCount(1);
    present_info.setPSwapchains(&swapchain.get());
    present_info.setPImageIndices(&index.value);
    auto result = present_queue.presentKHR(present_info);
    if (result != vk::Result::eSuccess)
        throw std::runtime_error("Failed to present Vulkan");

    device->waitIdle();
}
void vulkan::query_extent()
{
    int width = 0, height = 0;
    SDL_Vulkan_GetDrawableSize(window.handle, &width, &height);
    extent = vk::Extent2D(width, height);
}
} // namespace p201