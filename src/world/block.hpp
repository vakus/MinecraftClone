#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

#include "../graphics/vertex.hpp"
#include "../graphics/GameObject3D.hpp"

#include "../logger.hpp"


#define BLOCK_SHADE_NO_SHADE \
    {                        \
        1.0f, 1.0f, 1.0f     \
    }
#define BLOCK_SHADE_TOP  \
    {                    \
        1.0f, 1.0f, 1.0f \
    }
#define BLOCK_SHADE_SIDE \
    {                    \
        0.8f, 0.8f, 0.8f \
    }
#define BLOCK_SHADE_BOTTOM \
    {                      \
        0.6f, 0.6f, 0.6f   \
    }

class block
{
public:
    virtual int getId() = 0;
    virtual bool isTransparent() = 0;
    virtual GameObject3D getMesh(int FaceFlags) = 0;
    static std::vector<block*> BLOCKS{};
};

enum BlockFace
{
    TOP = 0b000001,
    BOTTOM = 0b000010,
    LEFT = 0b000100,
    RIGHT = 0b001000,
    FRONT = 0b010000,
    BACK = 0b100000
};

enum TextureCoordType
{
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

glm::vec2 getTextureCoord(uint x, uint y, TextureCoordType textureCoordType);
void blockInitialise();
#endif