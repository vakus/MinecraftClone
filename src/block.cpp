#include "block.hpp"

#define SHADE_TOP {1.0f, 1.0f, 1.0f}
#define SHADE_SIDE {0.8f, 0.8f, 0.8f}
#define SHADE_BOTTOM {0.6f, 0.6f, 0.6f}

void block::initialise(std::vector<block> *BLOCKS)
{
    //BLOCKS.resize(2);
    //dirt

    block dirt{
        {
            //top
            {{0.0f, 0.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_LEFT), SHADE_TOP},
            {{1.0f, 0.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_LEFT), SHADE_TOP},
            {{1.0f, 1.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_RIGHT), SHADE_TOP},
            {{0.0f, 1.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_RIGHT), SHADE_TOP},

            //front
            {{0.0f, 0.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_RIGHT), SHADE_SIDE},
            {{1.0f, 0.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_RIGHT), SHADE_SIDE},
            {{0.0f, 0.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_LEFT), SHADE_SIDE},
            {{1.0f, 0.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_LEFT), SHADE_SIDE},

            //back
            {{0.0f, 1.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_RIGHT), SHADE_SIDE},
            {{1.0f, 1.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_RIGHT), SHADE_SIDE},
            {{0.0f, 1.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_LEFT), SHADE_SIDE},
            {{1.0f, 1.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_LEFT), SHADE_SIDE},

            //left
            {{1.0f, 0.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_RIGHT), SHADE_SIDE},
            {{1.0f, 1.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_RIGHT), SHADE_SIDE},
            {{1.0f, 0.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_LEFT), SHADE_SIDE},
            {{1.0f, 1.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_LEFT), SHADE_SIDE},

            //right
            {{0.0f, 0.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_RIGHT), SHADE_SIDE},
            {{0.0f, 1.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_RIGHT), SHADE_SIDE},
            {{0.0f, 0.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_LEFT), SHADE_SIDE},
            {{0.0f, 1.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_LEFT), SHADE_SIDE},

            //bottom
            {{0.0f, 0.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_LEFT), SHADE_BOTTOM},
            {{1.0f, 0.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_LEFT), SHADE_BOTTOM},
            {{1.0f, 1.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_RIGHT), SHADE_BOTTOM},
            {{0.0f, 1.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_RIGHT), SHADE_BOTTOM} //
        },
        {
            2, 1, 0, 0, 3, 2,       //top
            4, 5, 7, 7, 6, 4,       //front
            11, 9, 8, 8, 10, 11,    //back
            12, 13, 14, 13, 15, 14, //left
            18, 17, 16, 18, 19, 17, //right
            20, 21, 22, 22, 23, 20  //bottom
        },
        1};

    BLOCKS->push_back(dirt);

    block stone{
        {
            //top
            {{0.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), SHADE_TOP},
            {{1.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), SHADE_TOP},
            {{1.0f, 1.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), SHADE_TOP},
            {{0.0f, 1.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), SHADE_TOP},

            //front
            {{0.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), SHADE_SIDE},
            {{1.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), SHADE_SIDE},
            {{0.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), SHADE_SIDE},
            {{1.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), SHADE_SIDE},

            //back
            {{0.0f, 1.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), SHADE_SIDE},
            {{1.0f, 1.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), SHADE_SIDE},
            {{0.0f, 1.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), SHADE_SIDE},
            {{1.0f, 1.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), SHADE_SIDE},

            //left
            {{1.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), SHADE_SIDE},
            {{1.0f, 1.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), SHADE_SIDE},
            {{1.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), SHADE_SIDE},
            {{1.0f, 1.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), SHADE_SIDE},

            //right
            {{0.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), SHADE_SIDE},
            {{0.0f, 1.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), SHADE_SIDE},
            {{0.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), SHADE_SIDE},
            {{0.0f, 1.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), SHADE_SIDE},

            //bottom
            {{0.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), SHADE_BOTTOM},
            {{1.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), SHADE_BOTTOM},
            {{1.0f, 1.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), SHADE_BOTTOM},
            {{0.0f, 1.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), SHADE_BOTTOM} //
        },
        {
            2, 1, 0, 0, 3, 2,       //top
            4, 5, 7, 7, 6, 4,       //front
            11, 9, 8, 8, 10, 11,    //back
            12, 13, 14, 13, 15, 14, //left
            18, 17, 16, 18, 19, 17, //right
            20, 21, 22, 22, 23, 20  //bottom
        },
        2};
    BLOCKS->push_back(stone);
}

glm::vec2 getTextureCoord(uint x, uint y, TextureCoordType textureCoordType)
{

    if (textureCoordType == TextureCoordType::TOP_RIGHT)
    {
        x++;
    }
    else if (textureCoordType == TextureCoordType::BOTTOM_LEFT)
    {
        y++;
    }
    else if (textureCoordType == TextureCoordType::BOTTOM_RIGHT)
    {
        y++;
        x++;
    }

    float baseX = x / 10.0f;
    float baseY = y / 10.0f;

    return glm::vec2(baseX, baseY);
}