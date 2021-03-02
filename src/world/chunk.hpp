#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_BLOCK_WIDTH 16 //x
#define CHUNK_BLOCK_HEIGHT 16 //y
#define CHUNK_BLOCK_DEPTH 16 //z

#include <array>
#include <vector>

#include "block.hpp"

#include "../graphics/GameObject3D.hpp"

class chunk{
    public:
        chunk();
        void setBlock(int x, int y, int z, block* b);
        GameObject3D getMesh();
    private:
        bool recreate;
        GameObject3D cachedMesh;
        std::vector<std::vector<std::vector<block*>>> blocks;
};

#endif