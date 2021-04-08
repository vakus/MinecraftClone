#ifndef CHUNK_H
#define CHUNK_H

/**
 * Specifies how many blocks should be on each axis in chunk
 */
#define CHUNK_BLOCK_SIZE 16

#include <array>
#include <vector>
class Chunk;
#include "block.hpp"
#include "world.hpp"

#include "../graphics/GameObject3D.hpp"

class Chunk{
    public:
        /**
         * The position of chunk in the world
         */
        const glm::ivec3 pos;

        Chunk(glm::ivec3 position, World* w);
        /**
         * Sets block at relative `pos` to `b`
         */
        void SetBlock(glm::ivec3 pos, Block* b);
        /**
         * Sets block at relative `x`/`y`/`z` to `b`
         */
        void SetBlock(int x, int y, int z, Block* b);
        /**
         * Gets block at relative `pos`.
         */
        Block* GetBlock(glm::ivec3 pos);
        /**
         * Gets block at relative `x`/`y`/`z`.
         */
        Block* GetBlock(int x, int y, int z);
        /**
         * Gets chunk's non-transparent and non-translucent mesh
         */
        GameObject3D GetMesh();
        /**
         * Gets chunk's transparent and translucent mesh
         */
        GameObject3D GetTranslucentMesh();
        /**
         * Generates terrain in the chunk
         */
        void Generate();
        /**
         * Marks chunk meshes to be recreated
         */
        void ForceRecreate();
    private:
        /**
         * Stores whatever chunk has been already generated
         */
        bool generated;
        /**
         * Stores whatever chunk mesh must be recreated
         */
        bool recreate;
        /**
         * Stores whatever chunk translucent mesh must be recreated
         */
        bool recreateTranslucent;
        /**
         * Stores cached chunk mesh
         */
        GameObject3D cachedMesh;
        /**
         * Stores cached chunk transparent mesh
         */
        GameObject3D cachedTranslucentMesh;
        /**
         * Stores blocks within the chunk
         */
        std::vector<std::vector<std::vector<Block*>>> blocks;
        /**
         * Stores pointer to World object
         */
        World* world;
};

#endif