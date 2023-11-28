#pragma once
#include <pch.h>
#include <array>

namespace MZ {


    struct UniformBufferObject {
        alignas(16) glm::mat4 model;
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;
        alignas(16) glm::vec3 color;
        alignas(16) glm::vec3 playerPos;
    };


    struct Vertex
    {
        glm::vec3 pos;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 1> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 1> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            return attributeDescriptions;
        }

        bool operator==(const Vertex& other) const {
            return pos == other.pos;
        }

    };

}

namespace std {
    template<> struct hash<MZ::Vertex> {
        size_t operator()(MZ::Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ 3));
        }
    };
}
