#pragma once

#include <glm/mat4x4.hpp>
#include <unordered_map>
#include <vector>
#include <vulkan/vulkan.hpp>

#include "common.hpp"
#include "vk/Buffer.hpp"
#include "vk/DescriptorSetHandler.hpp"
#include "vk/Pipeline.hpp"
#include "vk/RenderPass.hpp"
#include "vk/Swapchain.hpp"
#include "vk/VulkanCommandContext.hpp"
#include "vk/VulkanMainContext.hpp"
#include "vk/Scene.hpp"
#include "Camera.hpp"

namespace ve
{
    struct UniformBufferObject {
        glm::mat4 M;
    };

    class VulkanRenderContext
    {
    public:
        VulkanRenderContext(const VulkanMainContext& vmc, VulkanCommandContext& vcc);
        void self_destruct();

    private:
        enum class SyncNames
        {
            SImageAvailable,
            SRenderFinished,
            FRenderFinished
        };

    public:
        UniformBufferObject ubo{
                glm::mat4(1.0f)};

        PushConstants pc{
                glm::mat4(1.0f)};

        const uint32_t frames_in_flight = 2;
        uint32_t current_frame = 0;
        const VulkanMainContext& vmc;
        VulkanCommandContext& vcc;
        DescriptorSetHandler dsh;
        std::vector<ve::Buffer> uniform_buffers;
        std::unordered_map<SyncNames, std::vector<uint32_t>> sync_indices;
        std::vector<std::pair<glm::mat4, Mesh>> meshes;
        std::vector<Image> images;
        vk::SurfaceFormatKHR surface_format;
        vk::Format depth_format;
        RenderPass render_pass;
        Swapchain swapchain;
        Pipeline pipeline;
        std::vector<Scene> scenes;

        void draw_frame(const Camera& camera, float time_diff);
        vk::Extent2D recreate_swapchain();

    private:
        vk::SurfaceFormatKHR choose_surface_format();
        vk::Format choose_depth_format();
        void record_graphics_command_buffer(uint32_t image_idx, const glm::mat4& vp);
        void submit_graphics(vk::PipelineStageFlags wait_stage, uint32_t image_idx);
    };
}// namespace ve
