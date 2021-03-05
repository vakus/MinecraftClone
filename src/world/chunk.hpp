#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_BLOCK_WIDTH 16 //x
#define CHUNK_BLOCK_HEIGHT 16 //y
#define CHUNK_BLOCK_DEPTH 16 //z
#define CHUNK_GENERATION_SEA_LEVEL 64
#define CHUNK_GENERATION_MIN_Y 56
#define CHUNK_GENERATION_MAX_Y 72
#define CHUNK_GENERATION_OCTAVES 4

#include <array>
#include <vector>

#include "block.hpp"

#include "../graphics/GameObject3D.hpp"

class chunk{
    public:
        chunk(glm::ivec3 position);
        void setBlock(int x, int y, int z, block* b);
        block* getBlock(glm::ivec3 pos);
        block* getBlock(int x, int y, int z);
        GameObject3D getMesh();
        void generate(uint32_t seed);
    private:
        bool recreate;
        GameObject3D cachedMesh;
        std::vector<std::vector<std::vector<block*>>> blocks;
        glm::ivec3 pos;
};

#endif