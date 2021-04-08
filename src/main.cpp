#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string.h>
#include <cstdint>

#include "logger.hpp"
#include "application.hpp"
#include "world/block.hpp"
#include "world/world.hpp"

#include "world/generators/generator_flat.cpp"

int main(int argc, char *argv[])
{

    Application application;

//if `-D VALIDATIONLAYERS` is present in compilation, then validation layers will be enabled as default
#ifdef VALIDATIONLAYERS
    bool enableValidationLayers = true;
#else
    bool enableValidationLayers = false;
#endif

//if `-D LOGMIN=VALUE` is present in compilation then the value will be used for default logmin
#ifndef LOGMIN
    Logger::SetMinLog(Logger::INFO);
#elif LOGMIN == 1
    Logger::SetMinLog(Logger::FINER);
#elif LOGMIN == 2
    Logger::SetMinLog(Logger::FINE);
#elif LOGMIN == 3
    Logger::SetMinLog(Logger::INFO);
#elif LOGMIN == 4
    Logger::SetMinLog(Logger::WARN);
#elif LOGMIN == 5
    Logger::SetMinLog(Logger::ERROR);
#elif LOGMIN == 6
    Logger::SetMinLog(Logger::CRITICAL);
#else
    Logger::SetMinLog(Logger::INFO);
#endif

//if `-D LOGMAX=VALUE` is present in compilation then the value will be used for default logmax
#ifndef LOGMAX
    Logger::SetMaxLog(Logger::NONE);
#elif LOGMAX == 1
    Logger::SetMaxLog(Logger::FINER);
#elif LOGMAX == 2
    Logger::SetMaxLog(Logger::FINE);
#elif LOGMAX == 3
    Logger::SetMaxLog(Logger::INFO);
#elif LOGMAX == 4
    Logger::SetMaxLog(Logger::WARN);
#elif LOGMAX == 5
    Logger::SetMaxLog(Logger::ERROR);
#elif LOGMAX == 6
    Logger::SetMaxLog(Logger::CRITICAL);
#else
    Logger::SetMaxLog(Logger::NONE);
#endif

    //Check for runtime arguments
    //available arguments
    //  --logmin [finer|fine|info|warn/warning|error|none]  - will silence all logs below treshold
    //  --logmax [finer|fine|info|warn/warning|error|none]  - will silence all logs above treshold
    //  --validation-layers                                 - enable Vulkan Validation layers
    //  --validation-layer-khronos                          - enable Khronos' Vulkan Validation layer for right API usage
    //  --validation-layer-api-dump                         - enable Lunarg's Vulkan Validation layer for API dumping
    //  --flatland                                          - make the world flat
    if (argc > 0)
    {
        for (int x = 0; x < argc; x++)
        {
            std::string parg = argv[x];

            if (parg.compare("--logmin") == 0)
            {
                const std::string sarg = argv[x + 1];
                if (sarg.compare("finer") == 0)
                {
                    Logger::SetMinLog(Logger::FINER);
                }
                else if (sarg.compare("fine") == 0)
                {
                    Logger::SetMinLog(Logger::FINE);
                }
                else if (sarg.compare("info") == 0)
                {
                    Logger::SetMinLog(Logger::INFO);
                }
                else if (sarg.compare("warn") == 0 || sarg.compare("warning") == 0)
                {
                    Logger::SetMinLog(Logger::WARNING);
                }
                else if (sarg.compare("error") == 0)
                {
                    Logger::SetMinLog(Logger::ERROR);
                }
                else if (sarg.compare("critical") == 0)
                {
                    Logger::SetMinLog(Logger::CRITICAL);
                }
                else if (sarg.compare("none") == 0)
                {
                    Logger::SetMinLog(Logger::NONE);
                }
                else
                {
                    Logger::Warn("Ignoring unknown argument for --logmin: " + sarg);
                    std::cout << "unknown";
                }
            }
            else if (parg.compare("--logmax") == 0)
            {

                //parse the min
                std::string sarg = argv[x + 1];
                if (sarg.compare("finer") == 0)
                {
                    Logger::SetMaxLog(Logger::FINER);
                }
                else if (sarg.compare("fine") == 0)
                {
                    Logger::SetMaxLog(Logger::FINE);
                }
                else if (sarg.compare("info") == 0)
                {
                    Logger::SetMaxLog(Logger::INFO);
                }
                else if (sarg.compare("warn") == 0 || sarg.compare("warning") == 0)
                {
                    Logger::SetMaxLog(Logger::WARNING);
                }
                else if (sarg.compare("error") == 0)
                {
                    Logger::SetMaxLog(Logger::ERROR);
                }
                else if (sarg.compare("critical") == 0)
                {
                    Logger::SetMaxLog(Logger::CRITICAL);
                }
                else if (sarg.compare("none") == 0)
                {
                    Logger::SetMaxLog(Logger::NONE);
                }
                else
                {
                    Logger::Warn("Ignoring unknown argument for --logmax: " + sarg);
                }
            }
            else if (parg.compare("--validation-layers") == 0)
            {
                enableValidationLayers = true;
            }
            else if (parg.compare("--validation-layer-khronos") == 0)
            {
                enableValidationLayers = true;
                application.validationLayers.push_back("VK_LAYER_KHRONOS_validation");
            }
            else if (parg.compare("--validation-layer-api-dump") == 0)
            {
                enableValidationLayers = true;
                application.validationLayers.push_back("VK_LAYER_LUNARG_api_dump");
            }
            else if(parg.compare("--flatland") == 0){
                application.gameWorld.worldGenerator = new GeneratorFlat();
                application.PlayerPosition = glm::vec3(0, -10, 0);
            }
        }
    }

    const std::string compDate = __DATE__;
    const std::string compTime = __TIME__;

    Logger::Fine("Compiled on " + compDate + " at " + compTime);
#ifdef VALIDATIONLAYERS
    Logger::Fine("Compiled with Validation Layers enabled by default");
#endif
#ifdef LAYERS_KHRONOS_VALIDATION
    application.validationLayers.push_back("VK_LAYER_KHRONOS_validation");
    Logger::Fine("Compiled with Always On Validation Layer VK_LAYER_KHRONOS_validation");
#endif
#ifdef LAYERS_API_DUMP
    application.validationLayers.push_back("VK_LAYER_LUNARG_api_dump");
    Logger::Fine("Compiled with Always On Validation Layer VK_LAYER_LUNARG_api_dump");
#endif
    try
    {
        BlockInitialise();
        application.run(enableValidationLayers);
    }
    catch (std::exception &e)
    {
        Logger::Critical(e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}