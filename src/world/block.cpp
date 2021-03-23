#include "block.hpp"

#include "../blocks/BlockGrass.cpp"
#include "../blocks/BlockStone.cpp"
#include "../blocks/BlockDirt.cpp"
#include "../blocks/BlockFlowerYellow.cpp"
#include "../blocks/BlockOakLog.cpp"
#include "../blocks/BlockOakLeaves.cpp"
#include "../blocks/BlockWater.cpp"

void blockInitialise()
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

std::vector<block*> BLOCKS{};