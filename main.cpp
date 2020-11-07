#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <map>
#include <optional>
#include <set>

#include "logger.cpp"

namespace vulkan
{
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else
        {
            logger::error("handle for vkCreateDebugUtilsMessengerEXT could not be obtained");
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(instance, debugMessenger, pAllocator);
        }
    }
} // namespace vulkan

class Application
{
public:
    void run(bool enableValidationLayers)
    {
        initWindow(800, 600);
        initVulkan(enableValidationLayers);
        mainLoop();
        cleanup(enableValidationLayers);
    }

private:
    /**
     * Stores the handle to the window object
     */
    GLFWwindow *window;

    /**
     * Stores the handle to Vulkan instance
     */
    VkInstance instance;

    /**
     * 
     */
    VkDebugUtilsMessengerEXT debugMessenger;

    /**
     * Stores the handle to the physical device
     */
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    /**
     * Stores list of all validation layers we want to enable
     */
    const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"};

    const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    /**
     * Stores LogicalDevice
     */
    VkDevice device;

    /**
     * Stores graphics queue.
     */
    VkQueue queue;

    /**
     * stores window surface
     */
    VkSurfaceKHR surface;

    /**
     * stores presentation queue
     */
    VkQueue presentQueue;

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

    /**
     * This function runs window setup
     * 
     * it takes two arguments
     *  uint32_t width - the width of the initial window
     *  uint32_t height - the height of the initial window
     * 
     * after calling this function it will assign handle to `window` private variable
     */
    void
    initWindow(uint32_t width, uint32_t height)
    {
        glfwInit();

        //dont create OpenGL context (we are using Vulkan)
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        //prevent window from being resizable
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
    }

    /**
     * This function runs setup of Vulkan
     * 
     * after calling this function it will assign handle to `instance` private variable
     */
    void initVulkan(bool enableValidationLayers)
    {
        createInstance(enableValidationLayers);
        setupDebugMessanger(enableValidationLayers);
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice(enableValidationLayers);
    }

    /**
     * This function creates instance of Vulkan
     */
    void createInstance(bool enableValidationLayers)
    {

        if (enableValidationLayers && !checkValidationLayerSupport(validationLayers))
        {
            throw std::runtime_error("Validation layers requested, but not available.");
        }

        // Application info
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Vulkan";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        //list supported extensions
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> instanceExtensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, instanceExtensions.data());

        logger::finer("Available Extensions:");

        for (const auto &extension : instanceExtensions)
        {
            std::string tab = "\t\t";
            logger::finer(tab.append(extension.extensionName));
        }

        // Vulkan Global Extensions
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions(enableValidationLayers);
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        //this variable must be declared here to prevent garbage collection from if statement.
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo;
        }
        else
        {
            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to crete Vulkan instance!");
        }
    }

    /**
     * This function checks if wanted validation layers are available in the Vulkan.
     */
    bool checkValidationLayerSupport(std::vector<const char *> validationLayers)
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        logger::finer("Available Vulkan Validation Layers:");
        for (const auto &layerProperties : availableLayers)
        {
            std::string tab = "\t\t";
            logger::finer(tab.append(layerProperties.layerName));
        }

        for (const char *layerName : validationLayers)
        {
            bool layerFound = false;

            for (const auto &layerProperties : availableLayers)
            {
                if (strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound)
            {
                return false;
            }
        }

        return true;
    }

    std::vector<const char *> getRequiredExtensions(bool enableValidationLayers)
    {
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers)
        {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData)
    {

        if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
        {
            logger::finer(pCallbackData->pMessage);
        }
        else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
        {
            logger::fine(pCallbackData->pMessage);
        }
        else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
        {
            logger::warn(pCallbackData->pMessage);
        }
        else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
        {
            logger::error(pCallbackData->pMessage);
        }

        return VK_FALSE;
    }

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo)
    {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;
    }

    void setupDebugMessanger(bool enableValidationLayers)
    {
        if (enableValidationLayers)
        {
            VkDebugUtilsMessengerCreateInfoEXT createInfo;
            populateDebugMessengerCreateInfo(createInfo);

            if (vulkan::CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to set up debug messenger");
            }
        }
    }

    void pickPhysicalDevice()
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0)
        {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        std::multimap<int, VkPhysicalDevice> candidates;
        for (const auto &device : devices)
        {
            int score = rateDeviceSuitability(device);
            candidates.insert(std::make_pair(score, device));
        }

        if (candidates.rbegin()->first > 0)
        {
            physicalDevice = candidates.rbegin()->second;
        }
        else
        {
            throw std::runtime_error("failed to find a suitable GPU");
        }
    }

    int rateDeviceSuitability(VkPhysicalDevice device)
    {
        int score = 0;

        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;

        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            score += 1000;
        }

        QueueFamilyIndices indices = findQueueFamilies(device);

        if (!indices.isComplete() || !checkDeviceExtensionSupport(device))
        {
            return 0;
        }

        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
        if(!swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty()){
            return 0;
        }
        
        return score;
    }

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int x = 0;
        for (const auto &queueFamily : queueFamilies)
        {
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, x, surface, &presentSupport);
            if (presentSupport)
            {
                indices.presentFamily = x;
            }
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.graphicsFamily = x;
            }
            if (indices.graphicsFamily.has_value())
            {
                break;
            }
            x++;
        }

        return indices;
    }

    bool checkDeviceExtensionSupport(VkPhysicalDevice device)
    {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto &extension : availableExtensions)
        {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    void createLogicalDevice(bool enableValidationLayers)
    {
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        float queuePriority = 1.0f;

        for (uint32_t queueFamily : uniqueQueueFamilies)
        {

            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatuers{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatuers;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        if (enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create logical device!");
        }

        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &queue);
        vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
    }

    void createSurface()
    {
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
        {
            throw new std::runtime_error("Failed to create window surface");
        }
    }

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device){
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

        if(formatCount != 0){
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

        if(presentModeCount != 0){
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

    /**
     * This function is a loop which will be looped until the window should be closed
     */
    void mainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }

    /**
     * This function runs window and Vulkan cleanup
     */
    void cleanup(bool enableValidationLayers)
    {
        if (enableValidationLayers)
        {
            vulkan::DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }
        vkDestroyDevice(device, nullptr);

        vkDestroySurfaceKHR(instance, surface, nullptr);

        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }
};

int main(int argc, char *argv[])
{

    bool enableValidationLayers = false;

    logger::setMinLog(logger::INFO);
    logger::setMaxLog(logger::NONE);

    //check runtime arguments
    if (argc > 0)
    {
        for (int x = 0; x < argc - 1; x++)
        {
            std::string parg = argv[x];

            if (parg.compare("--logmin") == 0)
            {

                //parse the min
                const std::string sarg = argv[x + 1];
                if (sarg.compare("finer") == 0)
                {
                    logger::setMinLog(logger::FINER);
                }
                else if (sarg.compare("fine") == 0)
                {
                    logger::setMinLog(logger::FINE);
                }
                else if (sarg.compare("info") == 0)
                {
                    logger::setMinLog(logger::INFO);
                }
                else if (sarg.compare("warn") == 0 || sarg.compare("warning") == 0)
                {
                    logger::setMinLog(logger::WARNING);
                }
                else if (sarg.compare("error") == 0)
                {
                    logger::setMinLog(logger::ERROR);
                }
                else if (sarg.compare("critical") == 0)
                {
                    logger::setMinLog(logger::CRITICAL);
                }
                else if (sarg.compare("none") == 0)
                {
                    logger::setMinLog(logger::NONE);
                }
                else
                {
                    logger::warn("Ignoring unknown argument for --logmin: " + sarg);
                    std::cout << "unknown";
                }
            }
            else if (parg.compare("--logmax") == 0)
            {

                //parse the min
                std::string sarg = argv[x + 1];
                if (sarg.compare("finer") == 0)
                {
                    logger::setMaxLog(logger::FINER);
                }
                else if (sarg.compare("fine") == 0)
                {
                    logger::setMaxLog(logger::FINE);
                }
                else if (sarg.compare("info") == 0)
                {
                    logger::setMaxLog(logger::INFO);
                }
                else if (sarg.compare("warn") == 0 || sarg.compare("warning") == 0)
                {
                    logger::setMaxLog(logger::WARNING);
                }
                else if (sarg.compare("error") == 0)
                {
                    logger::setMaxLog(logger::ERROR);
                }
                else if (sarg.compare("critical") == 0)
                {
                    logger::setMaxLog(logger::CRITICAL);
                }
                else if (sarg.compare("none") == 0)
                {
                    logger::setMaxLog(logger::NONE);
                }
                else
                {
                    logger::warn("Ignoring unknown argument for --logmax: " + sarg);
                }
            }
            else if (parg.compare("--validation-layers") == 0)
            {
                enableValidationLayers = true;
            }
        }
    }

    Application application;

    try
    {
        application.run(enableValidationLayers);
    }
    catch (const std::exception &e)
    {
        logger::critical(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}