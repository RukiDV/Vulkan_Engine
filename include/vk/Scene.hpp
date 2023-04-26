#pragma once

#include "vk/common.hpp"
#include "vk/Model.hpp"
#include "vk/RenderObject.hpp"
#include "vk/VulkanStorageContext.hpp"

namespace ve
{
    class Scene
    {
    public:
        Scene(const VulkanMainContext& vmc, VulkanCommandContext& vcc, VulkanStorageContext& vsc);
        void construct(const RenderPass& render_pass);
        void self_destruct();
        void load(const std::string& path);
        void add_bindings();
        void translate(const std::string& model, const glm::vec3& trans);
        void scale(const std::string& model, const glm::vec3& scale);
        void rotate(const std::string& model, float degree, const glm::vec3& axis);
        DescriptorSetHandler& get_dsh(ShaderFlavor flavor);
        void draw(vk::CommandBuffer& cb, DrawInfo& di);

        bool loaded = false;

    private:
        const VulkanMainContext& vmc;
        VulkanCommandContext& vcc;
        VulkanStorageContext& vsc;
        std::unordered_map<ShaderFlavor, RenderObject> ros;
        std::vector<Material> materials;
        std::vector<std::vector<unsigned char>> texture_data;
        std::vector<glm::mat4> model_transformations;
        std::vector<ModelRenderData> model_render_data;
        std::unordered_map<std::string, uint32_t> model_handles;
        uint32_t vertex_buffer;
        uint32_t index_buffer;
        uint32_t material_buffer;
        uint32_t texture_image;
        std::vector<uint32_t> model_render_data_buffers;

        void add_model(Model& model, const std::string& name);
    };
} // namespace ve
