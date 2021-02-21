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
    //application.BLOCKS.resize(2);
    //block::initialise(application.BLOCKS);
    //application.world = chunk{};

    block b{};
/*
    b.verticies = {
        //top
        {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
        //front
        {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},

        //back
        {{0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        {{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        {{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},

        //left
        {{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        {{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},

        //right
        {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},

        //bottom
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}} //
        };
    b.indicies =
        {
            0, 1, 2, 2, 3, 0,       //top
            4, 5, 7, 7, 6, 4,       //front
            8, 9, 11, 11, 10, 8,    //back
            12, 13, 14, 14, 15, 13, //left
            16, 17, 18, 18, 19, 17, //right
            20, 21, 22, 22, 23, 20  //bottom
        };*/

    b.id = 1;

    application.BLOCKS.push_back(b);

    logger::finer("Dumping block ids:");
    for (int x = 0; x < application.BLOCKS.size(); x++)
    {
        logger::finer("Index: " + std::to_string(x) + " BlockID: " + std::to_string(application.BLOCKS[x].id));
    }

    application.world.blocks[0][0][0] = application.BLOCKS[0];
    /*
    for(int x = 0; x < 16; x++){
        for(int z = 0; z < 16; z++){
            logger::finer("Setting [" + std::to_string(x) + "][0][" + std::to_string(z) + "] with Block ID: " + std::to_string(application.BLOCKS[0].id));
            application.world.blocks[x][0][z] = application.BLOCKS[0];
        }
    }
    */
    try
    {
        application.run(enableValidationLayers);
    }
    catch (std::exception &e)
    {
        logger::critical(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}