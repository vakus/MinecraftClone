#ifndef GAME_OBJECT_3D_H
#define GAME_OBJECT_3D_H

#include <vector>
#include "vertex.hpp"

struct GameObject3D{
    std::vector<Vertex> verticies;
    std::vector<uint32_t> indicies;
};

#endif