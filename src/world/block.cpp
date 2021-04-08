#include "block.hpp"

#include "../blocks/BlockGrass.cpp"
#include "../blocks/BlockStone.cpp"
#include "../blocks/BlockDirt.cpp"
#include "../blocks/BlockFlowerYellow.cpp"
#include "../blocks/BlockFlowerRed.cpp"
#include "../blocks/BlockOakLog.cpp"
#include "../blocks/BlockOakLeaves.cpp"
#include "../blocks/BlockWater.cpp"
#include "../blocks/BlockSand.cpp"

/**
 * This function sets up list of all blocks available in the game
 * The blocks are stored in global variable `BLOCKS`
 */
void BlockInitialise()
{
    BlockGrass *grass = new BlockGrass();
    BLOCKS.push_back(grass);

    BlockStone *stone = new BlockStone();
    BLOCKS.push_back(stone);

    BlockDirt *dirt = new BlockDirt();
    BLOCKS.push_back(dirt);

    BlockFlowerYellow *flower = new BlockFlowerYellow();
    BLOCKS.push_back(flower);

    BlockOakLog *oakLog = new BlockOakLog();
    BLOCKS.push_back(oakLog);

    BlockOakLeaves *oakLeaves = new BlockOakLeaves();
    BLOCKS.push_back(oakLeaves);

    BlockWater *water = new BlockWater();
    BLOCKS.push_back(water);

    BlockFlowerRed *flowerRed = new BlockFlowerRed();
    BLOCKS.push_back(flowerRed);

    BlockSand *sand = new BlockSand();
    BLOCKS.push_back(sand);
}

/**
 * This function is a helper function that calculates normalised position in texture map,
 * based on provided X and Y coordinate where 0,0 is top left.
 */
glm::vec2 GetTextureCoord(uint x, uint y, TextureCoordType textureCoordType)
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

/**
 * This list stores all blocks available in the game
 */
std::vector<Block*> BLOCKS{};