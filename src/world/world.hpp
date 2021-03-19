#ifndef WORLD_H
#define WORLD_H

#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

class world;
#include "block.hpp"
#include "chunk.hpp"
#include "../graphics/GameObject3D.hpp"

#include <pthread.h>
#include <mutex>
#include <deque>
#include <condition_variable>

/**
 * specifies how many threads should be used for World Gen
 * I ran the test with 1 thread, 2 threads and 4 threads.
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
        uint32_t seed;
        world();
        world(uint32_t seed);
        void setBlock(glm::ivec3 pos, block* block);
        void setBlock(int x, int y, int z, block* block);
        block* getBlock(glm::ivec3 pos);
        block* getBlock(int x, int y, int z);
        GameObject3D getMesh(glm::ivec3 pos, int distance);
        static glm::ivec3 convertToChunk(glm::ivec3 pos);
        static glm::ivec3 convertToChunkRelative(glm::ivec3 pos);
        void stop();
    private:
        std::unordered_map<glm::ivec3, chunk*, ivec3Comparator, ivec3Comparator> chunks;


        std::vector<pthread_t> worldGenThread;
        std::mutex WorldGenMutex;
        std::deque<chunk*> WorldGenQueue;
        std::condition_variable WorldGenCond;
        bool WorldGenContinue = true;

        static void *WorldGenHelper(void *context);
        void *WorldGen();
};

#endif