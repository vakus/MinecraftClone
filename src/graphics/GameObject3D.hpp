#ifndef GAME_OBJECT_3D_H
#define GAME_OBJECT_3D_H

#include <vector>
#include "vertex.hpp"

/**
 * Represents 3D object used by Vulkan
 */
struct GameObject3D{
    /**
     * Stores Vertex used within a mesh
     */
    std::vector<Vertex> verticies;
    /**
     * Stores indexes which Vertex should be connected with each other.
     * This list should always be multiple of 3
     */
    std::vector<uint32_t> indicies;
};

#endif