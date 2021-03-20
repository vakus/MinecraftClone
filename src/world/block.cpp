#include "block.hpp"

#include "../blocks/grassBlock.cpp"
#include "../blocks/stone.cpp"
#include "../blocks/dirt.cpp"
#include "../blocks/flower.cpp"
#include "../blocks/OakLog.cpp"
#include "../blocks/OakLeaves.cpp"

void blockInitialise()
{
    BlockGrass *grass = new BlockGrass();
    BLOCKS.push_back(grass);

    BlockStone *stone = new BlockStone();
    BLOCKS.push_back(stone);

    BlockDirt *dirt = new BlockDirt();
    BLOCKS.push_back(dirt);

    BlockFlower *flower = new BlockFlower();
    BLOCKS.push_back(flower);

    BlockOakLog *oakLog = new BlockOakLog();
    BLOCKS.push_back(oakLog);

    BlockOakLeaves *oakLeaves = new BlockOakLeaves();
    BLOCKS.push_back(oakLeaves);
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