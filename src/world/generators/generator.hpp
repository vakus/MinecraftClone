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
    virtual void setSeed(uint32_t seed) = 0;
    virtual uint32_t getSeed() = 0;
    virtual void generate(std::vector<std::vector<std::vector<block*>>> &blocks, glm::ivec3 pos) = 0;
};


#endif