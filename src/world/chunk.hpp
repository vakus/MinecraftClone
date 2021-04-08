#ifndef CHUNK_H
#define CHUNK_H

/**
 * Specifies how many blocks should be on each axis in chunk
 */
#define CHUNK_BLOCK_SIZE 16

#include <array>
#include <vector>
class chunk;
#include "block.hpp"
#include "world.hpp"

#include "../graphics/GameObject3D.hpp"

class chunk{
    public:
        /**
         * The position of chunk in the world
         */
        const glm::ivec3 pos;

        chunk(glm::ivec3 position, world* w);
        /**
         * Sets block at relative `pos` to `b`
         */
        void setBlock(glm::ivec3 pos, block* b);
        /**
         * Sets block at relative `x`/`y`/`z` to `b`
         */
        void setBlock(int x, int y, int z, block* b);
        /**
         * Gets block at relative `pos`.
         */
        block* getBlock(glm::ivec3 pos);
        /**
         * Gets block at relative `x`/`y`/`z`.
         */
        block* getBlock(int x, int y, int z);
        /**
         * Gets chunk's non-transparent and non-translucent mesh
         */
        GameObject3D getMesh();
        /**
         * Gets chunk's transparent and translucent mesh
         */
        GameObject3D getTranslucentMesh();
        /**
         * Generates terrain in the chunk
         */
        void generate();
        /**
         * Marks chunk meshes to be recreated
         */
        void forceRecreate();
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
        std::vector<std::vector<std::vector<block*>>> blocks;
        /**
         * Stores pointer to World object
         */
        world* worldo;
};

#endif