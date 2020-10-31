#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>


class Application {
    public:
        void run(){
            initWindow(800, 600);
            initVulkan();
            mainLoop();
            cleanup();
        }

    private:

        /**
         * Stores the handle to the window object
         */
        GLFWwindow* window;

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
        void initWindow(uint32_t width, uint32_t height){
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
        void initVulkan(){
            createInstance();
        }

        /**
         * This function creates instance of Vulkan
         */
        void createInstance(){

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
            const char** glfwExtensions;

            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            createInfo.enabledExtensionCount = glfwExtensionCount;
            createInfo.ppEnabledExtensionNames = glfwExtensions;
            createInfo.enabledLayerCount = 0;

            if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS){
                throw std::runtime_error("Failed to crete Vulkan instance!");
            }
        }

        /**
         * This function is a loop which will be looped until the window should be closed
         */
        void mainLoop(){
            while(!glfwWindowShouldClose(window)){
                glfwPollEvents();
            }
        }

        /**
         * This function runs window and Vulkan cleanup
         */
        void cleanup(){
            glfwDestroyWindow(window);

            glfwTerminate();
        }
};

int main(){
    Application application;

    try{
        application.run();
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}