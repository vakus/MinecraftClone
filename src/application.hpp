#ifndef APPLICATION_H
#define APPLICATION_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <optional>
#include <array>
#include <vector>

#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "world/world.hpp"
#include "world/chunk.hpp"
#include "world/block.hpp"

#include "graphics/GameObject3D.hpp"


struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct UniformBufferObject
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
    glm::vec3 colorTint;
};

class Application{
    public:

        /**
         * Sensitivity of the mouse
         */
        float sensitivity = 0.01f;

        /**
         * The FOV that should be used for rendering.
         */
        float fov = 45.0f;

        /**
         * The near and far plane for rendering along z axis
         */
        float znear = 0.1f;
        float zfar = 16.0f;

        /**
         * The position of the player
         */
        glm::vec3 PlayerPosition = glm::vec3(0,0,0);

        /**
         * The rotation of the player's camera
         */
        glm::quat PlayerRotation = glm::quat(0,0,0,0);

        /**
         * world
         * TODO: replace chunk with actual world; chunk is fine for testing purposes
         */
        world gameWorld{};

        /**
         * GLFW window handle for the application
         */
        GLFWwindow *window;

        /**
         * Vulkan instance handle
         */
        VkInstance instance;

        /**
         * Handle for the debugging messenger which is used
         * by Vulkan to print info for ValidationLayers
         */
        VkDebugUtilsMessengerEXT debugMessenger;

        /**
         * Vulkan Physical Device
         * This device will be used to display graphics
         */
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

        /**
         * List of validation layers to be enabled for vulkan
         */
        std::vector<const char *> validationLayers = {
        };

        /**
         * device Extensions to be loaded by Vulkan
         */
        const std::vector<const char *> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        /**
         * Vulkan Logical Device
         */
        VkDevice device;

        /**
         * Graphics Queue from Logical Device. Used to task rendering jobs on the GPU
         */

        VkQueue graphicsQueue;

        /**
         * Window Surface Handle between GLFW and Vulkan
         */
        VkSurfaceKHR surface;

        /**
         * Presentation Queue from Logical Device. Used to queue rendered frame to be displayed
         */
        VkQueue presentQueue;

        /**
         * TODO: Swap Chain
         */
        VkSwapchainKHR swapChain;

        /**
         * TODO: ???
         */
        std::vector<VkImage> swapChainImages;

        /**
         * TODO: ???
         */
        std::vector<VkImageView> swapChainImageViews;

        /**
         * Information about which format should be used for images
         * in the swap chain
         */
        VkFormat swapChainImageFormat;

        /**
         * Information about extent of the swapChain
         * the extent presents maximum display height and width
         */
        VkExtent2D swapChainExtent;

        /**
         * Layout of Vulkan Pipeline
         */
        VkPipelineLayout pipelineLayout;

        /**
         * Handle for actual pipeline;
         */
        VkPipeline graphicsPipeline;

        /**
         * TODO: ???
         */
        VkRenderPass renderPass;

        /**
         * TODO: ???
         */
        std::vector<VkFramebuffer> swapChainFramebuffers;

        /**
         * TODO: ???
         */
        VkCommandPool commandPool;


        /**
         * TODO: ???
         */
        std::vector<VkCommandBuffer> commandBuffers;

        /**
         * Sync objects for images
         * TODO: clarify
         */
        std::vector<VkSemaphore> imageAvailableSemaphores;

        /**
         * Sync objects for frame rendering
         * This objects ensure that the frame is only drawn on screen
         * once rendering of the frame has been finished
         */
        std::vector<VkSemaphore> renderFinishSemaphores;

        /**
         * Sync object
         * TODO: clarify
         */
        std::vector<VkFence> inFlightFences;

        /**
         * TODO: ???
         */
        std::vector<VkFence> imagesInFlight;

        /**
         * maximum number of frames that can be
         * rendered at the same time.
         * 
         * THIS VALUE SHOULD NOT BE CHANGED DURING RUNTIME
         */
        const size_t MAX_FRAMES = 2;

        /**
         * Index of current frame, where MAX_FRAMES is maximum value
         * used together with sync objects
         */
        size_t currentFrame = 0;

        /**
         * informs whatever framebuffer needs to be resized
         * usually due to window resize.
         */
        bool framebufferResize = false;

        /**
         * Vertex buffer where we store all Vertex objects
         */
        VkBuffer vertexBuffer;

        /**
         * Information about memory where vertexBuffer is stored
         */
        VkDeviceMemory vertexBufferMemory;

        /**
         * Index buffer where connections between all Vertex objects
         * is stored
         */
        VkBuffer indexBuffer;

        /**
         * Information about memory where indexBuffer is stored
         */
        VkDeviceMemory indexBufferMemory;

        /**
         * UniformBufferObject buffer, which is passed to shader
         * used to pass data to modify current rendering
         */
        std::vector<VkBuffer> uniformBuffers;
        /**
         * Information about memory where UniformBufferObjects are stored
         * This list should always be syncronized with uniformBuffers
         */
        std::vector<VkDeviceMemory> uniformBuffersMemory;

        /**
         * TODO: ???
         */
        VkDescriptorSetLayout descriptorLayout;

        /**
         * TODO: ???
         */
        VkDescriptorPool descriptorPool;

        /**
         * TODO: ???
         */
        std::vector<VkDescriptorSet> descriptorSets;

        /**
         * Map where all textures are stored
         */
        VkImage textureImage;

        /**
         * Information about memory where textureImage is stored
         */
        VkDeviceMemory textureImageMemory;

        /**
         * TODO: ???
         */
        VkImageView textureImageView;

        /**
         * Sampler used for rendering of textures
         */
        VkSampler textureSampler;

        /**
         * Depth image used to render 3d graphics
         */
        VkImage depthImage;

        /**
         * Information about memory where depthImage is stored
         */
        VkDeviceMemory depthImageMemory;

        /**
         * TODO: ???
         */
        VkImageView depthImageView;


        void run(bool enableValidationLayers);

        void initWindow(uint32_t width, uint32_t height);

        void initVulkan(bool enableValidationLayers);
        
        void createDepthResources();

        VkFormat findSupportedFormat(
            const std::vector<VkFormat> &candidates,
            VkImageTiling tiling,
            VkFormatFeatureFlags features
        );

        VkFormat findDepthFormat();

        bool hasStencilComponent(VkFormat format);

        void createImageSampler();

        void createTextureImageView();

        VkImageView createImageView(
            VkImage image,
            VkFormat format,
            VkImageAspectFlags aspectFlags
        );

        void createTextureImage(const char *pathToTexture);

        void copyBufferToImage(
            VkBuffer buffer,
            VkImage image,
            uint32_t width,
            uint32_t height
        );

        void createImage(
            uint32_t width,
            uint32_t height,
            VkFormat format,
            VkImageTiling tiling,
            VkImageUsageFlags usage,
            VkMemoryPropertyFlags properties,
            VkImage &image,
            VkDeviceMemory &imageMemory
        );

        VkCommandBuffer beginSingleTimeCommands();

        void endSingleTimeBuffer(VkCommandBuffer commandBuffer);

        void createDescriptorSet();

        void createDescriptorPool();

        void updateUniformBuffer(uint32_t currentImage);

        void createUniformBuffers();

        void createDescriptorSetLayout();

        void createIndexBuffer(GameObject3D gameObject);

        void createBuffer(
            VkDeviceSize size,
            VkBufferUsageFlags usage,
            VkMemoryPropertyFlags properties,
            VkBuffer &buffer,
            VkDeviceMemory &bufferMemory
        );

        void copyBuffer(
            VkBuffer src,
            VkBuffer dst,
            VkDeviceSize size
        );

        void transitionImageLayout(
            VkImage image,
            VkFormat format,
            VkImageLayout oldLayout,
            VkImageLayout newLayout
        );

        void createVertexBuffer(GameObject3D gameObject);

        uint32_t findMemoryType(
            uint32_t filter,
            VkMemoryPropertyFlags properties
        );

        void createSyncObjects();

        void createCommandBuffers(GameObject3D gameObject);

        void createCommandPool();

        void createFramebuffers();

        void createRenderPass();

        void createGraphicsPipeline();

        VkShaderModule createShaderModule(const std::vector<char> &code);

        void createImageViews();

        void createSwapChain();

        void createInstance(bool enableValidationLayers);

        bool checkValidationLayerSupport(std::vector<const char *>validationLayers);

        std::vector<const char*> getRequiredExtensions(bool enableValidationLayers);

        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

        void setupDebugMessenger(bool enableValidationLayers);

        void pickPhysicalDevice();

        int rateDeviceSuitability(VkPhysicalDevice device);

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        void createLogicalDevice(bool enableValidationLayers);

        void createSurface();

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

        void mainLoop();

        void drawFrame();
        
        void recreateSwapChain();

        void cleanupSwapChain();

        void cleanup(bool enableValidationLayers);
};
#endif