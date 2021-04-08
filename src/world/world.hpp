#ifndef WORLD_H
#define WORLD_H

#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

class World;
#include "block.hpp"
#include "chunk.hpp"
#include "../graphics/GameObject3D.hpp"

#include <pthread.h>
#include <mutex>
#include <deque>
#include <condition_variable>

#include "generators/generator.hpp"

/**
 * specifies how many threads should be used for World Gen
 * I ran the test with 1 thread, 2 threads and 4 threads.
 * 
 * When using 1 thread the speed was too slow and player
 * could out run the world generation
 * 
 * When using 2 threads the speed was fast enough for the
 * chunks to generate before the player reached them, but
 * was still able to see generation artifacts
 * 
 * When using 4 threads similar effect to running with two threads
 * was observed
 */
#define WORLDGEN_THREAD_COUNT_MAX 2

/**
 * Comparators for unordered map of chunks
 */
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

class World{
    public:
        /**
         * Stores the seed of the world
         */
        uint32_t seed;
        World();
        World(uint32_t seed);
        World(uint32_t wseed, Generator* wworldGenerator);
        /**
         * Sets block to `block` at absolute `pos`
         */
        void SetBlock(glm::ivec3 pos, Block* block);
        /**
         * Sets block to `block` at absolute x/y/z
         */
        void SetBlock(int x, int y, int z, Block* block);
        /**
         * Gets block at absolute `pos`
         */
        Block* GetBlock(glm::ivec3 pos);
        /**
         * Gets block at absolute x/y/z
         */
        Block* GetBlock(int x, int y, int z);
        /**
         * Gets mesh of the world
         */
        GameObject3D GetMesh(glm::ivec3 pos, int distance);
        /**
         * Converts absolute coordinate to coordinate of chunk
         */
        static glm::ivec3 ConvertToChunk(glm::ivec3 pos);
        /**
         * Converts absolute coordinate to coordinate of block within chunk
         */
        static glm::ivec3 ConvertToChunkRelative(glm::ivec3 pos);
        /**
         * Stops the world multithreading
         */
        void Stop();
        /**
         * Stores the world generator used by this world.
         */
        Generator* worldGenerator;
    private:
        /**
         * Stores chunks within the world
         */
        std::unordered_map<glm::ivec3, Chunk*, ivec3Comparator, ivec3Comparator> chunks;

        /**
         * Stores list of threads that are used for world generator
         */
        std::vector<pthread_t> worldGenThread;
        /**
         * Mutex for world generator threads
         */
        std::mutex worldGenMutex;
        /**
         * Queue for chunks to be generated by other treads
         */
        std::deque<Chunk*> worldGenQueue;
        /**
         * Used to block generator threads
         */
        std::condition_variable worldGenCond;
        /**
         * Specifies whatever generator threads should continue to work
         */
        bool worldGenContinue = true;

        /**
         * Helper function for world::WorldGen
         * Allows passage of the world object
         */
        static void *WorldGenHelper(void *context);
        /**
         * generator thread loop
         */
        void *WorldGen();
};

#endif