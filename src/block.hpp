#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "vertex.hpp"

class block{
    public:
    std::vector<Vertex> verticies = {
        //top
        {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

        //front
        {{0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},

        //back
        {{0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
        {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},

        //left
        {{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},

        //right
        {{0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},

        //bottom
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}} //
        };
    std::vector<uint32_t> indicies =
        {
            0, 1, 2, 2, 3, 0,       //top
            4, 5, 7, 7, 6, 4,       //front
            8, 9, 11, 11, 10, 8,    //back
            12, 13, 14, 14, 15, 13, //left
            16, 17, 18, 18, 19, 17, //right
            20, 21, 22, 22, 23, 20  //bottom
        };

    int id;

    static void initialise(std::vector<block> BLOCKS);
};

enum TextureCoordType{
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

glm::vec2 getTextureCoord(uint x, uint y, TextureCoordType textureCoordType);

#endif