#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "vertex.hpp"

class block{
    public:
    std::vector<Vertex> verticies;
    std::vector<uint32_t> indicies;

    int id;

    static void initialise(std::vector<block> *BLOCKS);
};

enum TextureCoordType{
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

glm::vec2 getTextureCoord(uint x, uint y, TextureCoordType textureCoordType);

#endif