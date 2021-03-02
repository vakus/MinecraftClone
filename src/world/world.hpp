#ifndef WORLD_H
#define WORLD_H

#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <unordered_map>

#include "block.hpp"
#include "chunk.hpp"
#include "../GameObject3D.hpp"

struct ivec3Comparator{
    size_t operator()(glm::ivec3 const& k)const{
        return ((std::hash<int>()(k.x)
               ^ (std::hash<int>()(k.y) << 1)) >> 1)
               ^ (std::hash<int>()(k.z) << 1);
    }
    bool operator()(glm::ivec3 const& lhs, glm::ivec3 const& rhs)const{
        return 
            lhs.x == rhs.x
            && lhs.y == rhs.y
            && lhs.z == rhs.z;
    }
};

class world{
    public:
        void setBlock(glm::ivec3 pos, block* block);
        void setBlock(int x, int y, int z, block* block);
        GameObject3D getMesh(glm::ivec3 pos, int distance);
    private:
        std::unordered_map<glm::ivec3, chunk*, ivec3Comparator, ivec3Comparator> chunks;
};

#endif