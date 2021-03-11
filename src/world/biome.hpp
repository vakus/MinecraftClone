#pragma once

#include "block.hpp"
#include <vector>

enum BiomeType{
    PLAINS,
    OCEAN,
    OAK_FOREST,
    DESERT
};

struct Biome{
    BiomeType type;
    int MinHeight;
    int MaxHeight;
    int octaves;
    std::vector<block*> TopBlocks;
    std::vector<block*> BottomBlocks;

    static void initBiomes();
};

extern std::vector<Biome> Biomes;