#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#include "logger.cpp"

class Application
{
public:
    void run()
    {
        initWindow(800, 600);
        initVulkan();
        mainLoop();
        cleanup();
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
     * This function runs window setup
     * 
     * it takes two arguments
     *  uint32_t width - the width of the initial window
     *  uint32_t height - the height of the initial window
     * 
     * after calling this function it will assign handle to `window` private variable
     */
    void initWindow(uint32_t width, uint32_t height)
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
    void initVulkan()
    {
        createInstance();
    }

    /**
         * This function creates instance of Vulkan
         */
    void createInstance()
    {

        // Application info
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Vulkan";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // Vulkan Global Extensions
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // get GLFW extensions
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        //list supported extensions
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        logger::info("Available Extensions:");

        for (const auto &extension : extensions)
        {
            std::string tab = "\t\t";
            logger::info(tab.append(extension.extensionName));
        }

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to crete Vulkan instance!");
        }
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
    void cleanup()
    {
        glfwDestroyWindow(window);

        glfwTerminate();
    }
};

int main(int argc, char *argv[])
{

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
        }
    }

    Application application;

    try
    {
        application.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}