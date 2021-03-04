#include "block.hpp"

#include "../blocks/dirt.cpp"
#include "../blocks/stone.cpp"

void blockInitialise()
{
    BlockDirt *dirt = new BlockDirt();
    BLOCKS.push_back(dirt);

    BlockStone *stone = new BlockStone();
    BLOCKS.push_back(stone);
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