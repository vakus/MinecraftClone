#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

#include "../graphics/vertex.hpp"
#include "../graphics/GameObject3D.hpp"

#include "../logger.hpp"


/**
 * Do not add extra shade on the block faces
 */
#define BLOCK_SHADE_NO_SHADE \
    {                        \
        1.0f, 1.0f, 1.0f     \
    }

/**
 * Shade to be added on top block face
 * This can be used to make separate blocks more distinct
 */
#define BLOCK_SHADE_TOP  \
    {                    \
        1.0f, 1.0f, 1.0f \
    }
/**
 * Shade to be added on sides of a block
 * This can be used to make separate blocks more distinct
 */
#define BLOCK_SHADE_SIDE \
    {                    \
        0.8f, 0.8f, 0.8f \
    }
/**
 * Shade to be added on bottom of block
 * This can be used to make separate blocks more distinct
 */
#define BLOCK_SHADE_BOTTOM \
    {                      \
        0.6f, 0.6f, 0.6f   \
    }

class block
{
public:
    /**
     * Defines whatever the block is transparent/translucent or not
     * If the block is transparent/translucent then blocks' face covered by this block will still be rendered
     * If the block is not transparent then blocks' face covered by this block will not be rendered
     */
    virtual bool isTransparent() = 0;
    /**
     * Gets 3D mesh of the block
     * FaceFlags specify which faces should be included in block.
     * e.g. if BlockFace::TOP is not present that means that top face of this block will not be visible
     */
    virtual GameObject3D getMesh(int FaceFlags) = 0;
};

/**
 * Used in combination with block::getMesh
 * Specifies block faces directions.
 * LEFT/RIGHT is on X axis
 * TOP/BOTTOM is on Y axis
 * FRONT/BACK is on Z axis
 */
enum BlockFace
{
    TOP = 0b000001,
    BOTTOM = 0b000010,
    LEFT = 0b000100,
    RIGHT = 0b001000,
    FRONT = 0b010000,
    BACK = 0b100000
};

/**
 * Used in combination with getTextureCoord
 * Specifies which vertex on texture should be represented
 */
enum TextureCoordType
{
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

/**
 * This list stores all blocks available in the game
 */
extern std::vector<block*> BLOCKS;

/**
 * This function is a helper function that calculates normalised position in texture map,
 * based on provided X and Y coordinate where 0,0 is top left.
 */
glm::vec2 getTextureCoord(uint x, uint y, TextureCoordType textureCoordType);

/**
 * This function sets up list of all blocks available in the game
 * The blocks are stored in global variable `BLOCKS`
 */
void blockInitialise();
#endif