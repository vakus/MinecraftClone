#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_BLOCK_WIDTH 16 //x
#define CHUNK_BLOCK_HEIGHT 16 //y
#define CHUNK_BLOCK_DEPTH 16 //z

#include <array>
#include <vector>

#include "block.hpp"
#include "GameObject3D.hpp"

class chunk{
    public:
        chunk();

        std::vector<std::vector<std::vector<block>>> blocks;

        GameObject3D getMesh();
};

#endif