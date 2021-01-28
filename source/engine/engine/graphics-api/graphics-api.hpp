
#pragma once
#include "../media-layer.hpp"
#include "../util.hpp"

#include <__common.hpp>
#include <array>
#include <shaderc/shaderc.hpp>
#include <vulkan/vulkan.hpp>

namespace p201
{
class vulkan
{
public:
    struct vertex
    {
        vector_2 position;
        vector_3 color;

        vertex() = default;
        vertex(const vector_2& position, const vector_3& color)
            : position(position), color(color)
        { }

        static vk::VertexInputBindingDescription binding_desc()
        {
            auto result = vk::VertexInputBindingDescription();

            result.setBinding(0);
            result.setStride(sizeof(vertex));

            return result;
        }
        static std::array<vk::VertexInputAttributeDescription, 2> attr_desc()
        {
            auto result = std::array<vk::VertexInputAttributeDescription, 2>();

            result.at(0).binding  = 0;
            result.at(0).location = 0;
            result.at(0).format   = vk::Format::eR32G32Sfloat;
            result.at(0).offset   = offsetof(vertex, position);

            result.at(1).binding  = 0;
            result.at(1).location = 1;
            result.at(1).format   = vk::Format::eR32G32B32Sfloat;
            result.at(1).offset   = offsetof(vertex, color);

            return result;
        }
    };

private:
    /* CONTEXT OBJECTS */
    class window& window;

    /* PIPELINE */
    std::uint32_t graphics_index = ~0u;
    std::uint32_t present_index  = ~0u;

    /** @todo Triple buffering. */
    static constexpr std::size_t swapchain_image_count = 2;
    static constexpr vk::Format  format = vk::Format::eB8G8R8A8Unorm;
    std::vector<std::uint32_t>   queue_family_indices;
    vk::Extent2D                 extent;

    /* SHADER */
    using shader_kind                     = shaderc_shader_kind;
    static constexpr auto shader_infer    = shaderc_glsl_infer_from_source;
    static constexpr auto shader_vertex   = shaderc_glsl_vertex_shader;
    static constexpr auto shader_fragment = shaderc_glsl_fragment_shader;
    static constexpr auto shader_success  = shaderc_compilation_status_success;

protected:
    /* SHADER */
    shaderc::Compiler spirv;

    [[nodiscard]] vk::ShaderModuleCreateInfo
    create_shader(const std::string&, shader_kind, std::vector<std::uint32_t>&);

protected:
    /**
     * @brief Connects application to Vulkan library.
     * @see vulkan::create_instance()
     */
    vk::UniqueInstance instance;
    /**
     * @brief Connects Vulkan instance to window. Requires adding extension
     *        "VK_KHR_surface" (done by SDL/GLFW).
     * @see vulkan::create_surface()
     */
    vk::UniqueSurfaceKHR surface;
    /**
     * @brief Represents the GPU used.
     * @todo Impement functionality for external + Intel integrated GPU.
     */
    vk::PhysicalDevice gpu;
    /**
     * @brief Interface for physical device(s).
     * @see vulkan::create_device()
     */
    vk::UniqueDevice device;
    /**
     * @brief Contains the frame buffers used in rendering and swapping.
     *        The number of buffers is set by vulkan::swapchain_image_count.
     * @see vulkan::create_swapchain()
     */
    vk::UniqueSwapchainKHR swapchain;
    /**
     * @brief Views into the buffers in the swapchain.
     */
    std::vector<vk::UniqueImageView> image_views;
    /**
     * @brief Allows passing dynamic values into shaders.
     */
    vk::UniquePipelineLayout pipeline_layout;
    /**
     * @brief Indicates that the image view buffer is ready to be drawn on.
     */
    vk::UniqueSemaphore image_available;
    /**
     * @brief Indicates that rendering is done.
     */
    vk::UniqueSemaphore render_finished;
    /**
     * @brief Render pass used in graphics pipeline.
     * @see vulkan::create_pipeline()
     */
    vk::UniqueRenderPass render_pass;
    /**
     * @brief Graphics pipeline.
     * @see vulkan::create_pipeline()
     */
    vk::UniquePipeline pipeline;
    /**
     * @brief Frame buffers used in rendering.
     * @see vulkan::create_framebuffers()
     */
    std::vector<vk::UniqueFramebuffer> framebuffers;
    /**
     * @brief Command pool. No idea what this does yet.
     * @see vulkan::create_command_pool()
     */
    vk::UniqueCommandPool command_pool;
    /**
     * @brief Stores vertex inputs to pass to shaders.
     * @see vulkan::create_vertex_buffers()
     */
    vk::UniqueBuffer       vertex_buffer;
    vk::UniqueDeviceMemory device_memory;
    /**
     * @brief Command buffers. No idea what this does yet.
     * @see vulkan::create_command_pool()
     */
    std::vector<vk::UniqueCommandBuffer> command_buffers;
    vk::Queue                            device_queue;
    vk::Queue                            present_queue;

    /* FUNCTIONS */
    /* INIT */
    /** @see vulkan::instance */
    void create_instance();
    /** @see vulkan::surface */
    void create_surface();
    /** @see vulkan::device */
    void create_device();
    /** @see vulkan::swapchain */
    void create_swapchain();

    /* PIPELINE */
    /** @see vulkan::pipeline */
    void create_pipeline();
    /** @see vulkan::framebuffers */
    void create_framebuffers();
    void create_command_pool();
    void create_vertex_buffer();
    void create_command_buffers();

public:
    vulkan(class window&);
    ~vulkan() = default;

    /* INIT */
    void start();

    /* DRAWING */
    /** @todo Temp. */
    void draw();

    /* UTIL */
    void query_extent();
};
} // namespace p201