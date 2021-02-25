#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string.h>
#include <cstdint>

#include "logger.hpp"
#include "application.hpp"
#include "block.hpp"

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
    logger::setMinLog(logger::INFO);
#elif LOGMIN == 1
    logger::setMinLog(logger::FINER);
#elif LOGMIN == 2
    logger::setMinLog(logger::FINE);
#elif LOGMIN == 3
    logger::setMinLog(logger::INFO);
#elif LOGMIN == 4
    logger::setMinLog(logger::WARN);
#elif LOGMIN == 5
    logger::setMinLog(logger::ERROR);
#elif LOGMIN == 6
    logger::setMinLog(logger::CRITICAL);
#else
    logger::setMinLog(logger::INFO);
#endif

//if `-D LOGMAX=VALUE` is present in compilation then the value will be used for default logmax
#ifndef LOGMAX
    logger::setMaxLog(logger::NONE);
#elif LOGMAX == 1
    logger::setMaxLog(logger::FINER);
#elif LOGMAX == 2
    logger::setMaxLog(logger::FINE);
#elif LOGMAX == 3
    logger::setMaxLog(logger::INFO);
#elif LOGMAX == 4
    logger::setMaxLog(logger::WARN);
#elif LOGMAX == 5
    logger::setMaxLog(logger::ERROR);
#elif LOGMAX == 6
    logger::setMaxLog(logger::CRITICAL);
#else
    logger::setMaxLog(logger::NONE);
#endif

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
        }
    }

    const std::string compDate = __DATE__;
    const std::string compTime = __TIME__;

    logger::fine("Compiled on " + compDate + " at " + compTime);
#ifdef VALIDATIONLAYERS
    logger::fine("Compiled with Validation Layers enabled by default");
#endif
#ifdef LAYERS_KHRONOS_VALIDATION
    application.validationLayers.push_back("VK_LAYER_KHRONOS_validation");
    logger::fine("Compiled with Always On Validation Layer VK_LAYER_KHRONOS_validation");
#endif
#ifdef LAYERS_API_DUMP
    application.validationLayers.push_back("VK_LAYER_LUNARG_api_dump");
    logger::fine("Compiled with Always On Validation Layer VK_LAYER_LUNARG_api_dump");
#endif
    try
    {
        blockInitialise(&application.BLOCKS);

        logger::info("Dumping block ids. size: " + std::to_string(application.BLOCKS.size()));
        for (size_t x = 0; x < application.BLOCKS.size(); x++)
        {
            logger::info("Index: " + std::to_string(x) + " BlockID: " + std::to_string(application.BLOCKS[x]->getId()));
        }

        for (int x = 0; x < 16; x++)
        {
            for (int z = 0; z < 16; z++)
            {
                logger::finer("Setting [" + std::to_string(x) + "][0][" + std::to_string(z) + "] with Block ID: " + std::to_string(application.BLOCKS[0]->getId()));
                application.world.setBlock(x, 0, z, application.BLOCKS[0]);
                application.world.setBlock(x, 4, z, application.BLOCKS[1]);
            }
        }
        application.world.setBlock(3, 1, 4, application.BLOCKS[1]);
        application.world.setBlock(5, 1, 4, application.BLOCKS[1]);
        application.world.setBlock(4, 1, 3, application.BLOCKS[1]);
        application.world.setBlock(4, 1, 5, application.BLOCKS[1]);
        application.world.setBlock(4, 2, 4, application.BLOCKS[1]);

        application.world.setBlock(4, 8, 4, application.BLOCKS[1]);
        application.world.setBlock(4, 8, 5, application.BLOCKS[1]);

        application.world.setBlock(8, 8, 4, application.BLOCKS[1]);
        application.world.setBlock(7, 8, 4, application.BLOCKS[1]);

        application.world.setBlock(8, 8, 8, application.BLOCKS[1]);
        application.world.setBlock(8, 9, 8, application.BLOCKS[1]);

        application.run(enableValidationLayers);
    }
    catch (std::exception &e)
    {
        logger::critical(e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}