#ifndef GENERATOR_H
#define GENERATOR_H

#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

#include "../block.hpp"

class Generator{
public:
    /**
     * Sets seed to be used by world generator
     */
    virtual void SetSeed(uint32_t seed) = 0;
    /**
     * Returns currently used seed by world generator
     */
    virtual uint32_t GetSeed() = 0;
    /**
     * Generates terrain within `&blocks` at chunk position `pos`
     */
    virtual void Generate(std::vector<std::vector<std::vector<Block*>>> &blocks, glm::ivec3 pos) = 0;
};


#endif