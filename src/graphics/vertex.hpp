#ifndef VERTEX_H
#define VERTEX_H

#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <array>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

struct Vertex{
    /**
     * Stores 3D absolute position where the vertex is
     */
    glm::vec3 pos;
    /**
     * Stores 2D normalised position of texture where the vertex corresponds
     */
    glm::vec2 texCoord;
    /**
     * Stores additional shade information that should be placed on this vertex
     */
    glm::vec3 shade;

    /**
     * This function specifies the size of Vertex and binding information for Vulkan
     */
    static VkVertexInputBindingDescription getBindingDescription()
    {
        VkVertexInputBindingDescription bindingDescription{};

        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    /**
     * This function specifies content of vertex and its sizes and type information for Vulkan
     */
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions()
    {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, texCoord);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, shade);

        return attributeDescriptions;
    }
};
#endif