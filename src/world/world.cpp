#include "world.hpp"

#include <stdlib.h>
#include <chrono>
#include <algorithm>

#include "generators/generator_default.cpp"

/**
 * Creates world with random seed and default terrain generator
 */
world::world(){
    seed = rand();
    worldGenThread.resize(WORLDGEN_THREAD_COUNT_MAX);
    for(size_t x = 0; x < WORLDGEN_THREAD_COUNT_MAX; x++){
        pthread_create(&worldGenThread[x], NULL, &world::WorldGenHelper, this);
    }
    worldGenerator = new GeneratorDefault(this);
    worldGenerator->setSeed(seed);
}

/**
 * Creates world with specified seed and default terrain generator
 */
world::world(uint32_t seed){
    this->seed = seed;
    worldGenThread.resize(WORLDGEN_THREAD_COUNT_MAX);
    for(size_t x = 0; x < WORLDGEN_THREAD_COUNT_MAX; x++){
        pthread_create(&worldGenThread[x], NULL, &world::WorldGenHelper, this);
    }
    worldGenerator = new GeneratorDefault(this);
    worldGenerator->setSeed(seed);
}

/**
 * Creates world with specified seed and specified terrain generator
 */
world::world(uint32_t seed, Generator* worldGenerator){
    this->seed = seed;
    worldGenThread.resize(WORLDGEN_THREAD_COUNT_MAX);
    for(size_t x = 0; x < WORLDGEN_THREAD_COUNT_MAX; x++){
        pthread_create(&worldGenThread[x], NULL, &world::WorldGenHelper, this);
    }
    this->worldGenerator = worldGenerator;
    this->worldGenerator->setSeed(seed);
}

/**
 * Sets `block` at absolute `pos`
 * If chunk does not exist, it will be created
 * 
 * FIXME: world::chunks is not thread safe
 */
void world::setBlock(glm::ivec3 pos, block* block){
    glm::ivec3 chunkPos = convertToChunk(pos);

    chunk* c = chunks[chunkPos];

    if(c == NULL){
        //if chunk doesnt exist simply create it
        c = new chunk(chunkPos, this);

        chunks[chunkPos] = c;
    }

    c->setBlock(convertToChunkRelative(pos), block);
}

/**
 * Sets `block` at absolute `x`/`y`/`z`
 * converts x/y/z to glm::ivec3 and calls setBlock(glm::ivec3, block*)
 */
void world::setBlock(int x, int y, int z, block* block){
    world::setBlock(glm::ivec3(x, y, z), block);
}

/**
 * Returns block at absolute `pos`
 * If chunk doesn't exist then it returns NULL
 */
block* world::getBlock(glm::ivec3 pos){
    glm::ivec3 chunkPos = convertToChunk(pos);

    chunk* c = chunks[chunkPos];

    if(c == NULL){
        //if the chunk doesnt exist we dont want to generate it (could cause cascading generation)
        return NULL;
    }

    return c->getBlock(convertToChunkRelative(pos));
}
/**
 * Returns block at absolute `x`/`y`/`z`
 * Converts x/y/z to glm::ivec3 and calls getBlock(glm::ivec3)
 */
block* world::getBlock(int x, int y, int z){
    return getBlock(glm::ivec3(x,y,z));
}

/**
 * Returns the mesh of the entire world, from `pos` limited to `distance` of chunks away
 * e.g. `distance` set to 3 would cause 7 by 7 by 7 chunks to be returned
 * (chunk in which `pos` is plus 3 chunks each direction)
 * 
 * FIXME: sometimes causes segmentation fault
 * FIXME: world::chunk is not thread safe (possibly causing segfault)
 * FIXME: Currently WorldGenCond is notified at least once per call to prevent notifications being missed by other threads.
 */
GameObject3D world::getMesh(glm::ivec3 pos, int distance){

    GameObject3D mesh;
    GameObject3D translucentMesh;

    glm::ivec3 targetChunk = convertToChunk(pos);

    for(int x = -distance; x <= distance; x++){
        for(int y = -distance; y <= distance; y++){
            for(int z = -distance; z <= distance; z++){
                glm::ivec3 actualPos = glm::ivec3(targetChunk);
                actualPos.x += x;
                actualPos.y += y;
                actualPos.z += z;
                actualPos *= -1;

                chunk* c = chunks[actualPos];
                if(c == NULL){
                    c = new chunk(actualPos, this);
                    
                    chunks[actualPos] = c;
                    
                    auto lock = std::unique_lock<std::mutex>(WorldGenMutex);
                    WorldGenQueue.push_back(c);
                    lock.unlock();
                    WorldGenCond.notify_all();
                    continue;
                }
                GameObject3D chunkMesh = c->getMesh();

                uint32_t verticiesOffset = mesh.verticies.size();
                std::for_each(chunkMesh.indicies.begin(), chunkMesh.indicies.end(), [verticiesOffset](uint32_t &x){x += verticiesOffset;});
                mesh.indicies.insert(mesh.indicies.end(), chunkMesh.indicies.begin(), chunkMesh.indicies.end());
                mesh.verticies.insert(mesh.verticies.end(), chunkMesh.verticies.begin(), chunkMesh.verticies.end());

                GameObject3D translucentChunkMesh = c->getTranslucentMesh();

                verticiesOffset = translucentMesh.verticies.size();
                std::for_each(translucentChunkMesh.indicies.begin(), translucentChunkMesh.indicies.end(), [verticiesOffset](uint32_t &x){x += verticiesOffset;});
                translucentMesh.indicies.insert(translucentMesh.indicies.end(), translucentChunkMesh.indicies.begin(), translucentChunkMesh.indicies.end());
                translucentMesh.verticies.insert(translucentMesh.verticies.end(), translucentChunkMesh.verticies.begin(), translucentChunkMesh.verticies.end());
         
            }
        }
    }
    //FIXME this allows at least one chunk generated per frame
    // the problem however is that when a chunk is added to
    // worldgen queue and then thread is notified
    // the worldgen thread may miss next notifications
    //
    // while this prevents chunks from never being generated
    // this doesnt feel right
    WorldGenCond.notify_all();

    //we need to add translucent layer after normal layer
    
    int verticiesOffset = mesh.verticies.size();
    std::for_each(translucentMesh.indicies.begin(), translucentMesh.indicies.end(), [verticiesOffset](uint32_t &x){x += verticiesOffset;});
    mesh.indicies.insert(mesh.indicies.end(), translucentMesh.indicies.begin(), translucentMesh.indicies.end());
    mesh.verticies.insert(mesh.verticies.end(), translucentMesh.verticies.begin(), translucentMesh.verticies.end());

    //unfortunately if we try to render empty frame, vulkan will crash due to empty buffer
    //lets add junk triangle to make it not crash
    uint32_t offset = mesh.verticies.size();
    mesh.verticies.insert(mesh.verticies.end(), {
             {pos, {0,0}, {0,0,0}},
             {pos, {0,0}, {0,0,0}},
             {pos, {0,0}, {0,0,0}},
    });
    mesh.indicies.insert(mesh.indicies.end(), {
        offset, offset+1, offset+2
    });
    return mesh;
}

/**
 * This function converts absolute `pos` to a absolute chunk position
 */
glm::ivec3 world::convertToChunk(glm::ivec3 pos){
    if(pos.x % CHUNK_BLOCK_SIZE < 0){
        pos.x -= CHUNK_BLOCK_SIZE - 1;
    }
    if(pos.y % CHUNK_BLOCK_SIZE < 0){
        pos.y -= CHUNK_BLOCK_SIZE - 1;
    }
    if(pos.z % CHUNK_BLOCK_SIZE < 0){
        pos.z -= CHUNK_BLOCK_SIZE - 1;
    }

    int ChunkX = floor(pos.x / CHUNK_BLOCK_SIZE);
    int ChunkY = floor(pos.y / CHUNK_BLOCK_SIZE);
    int ChunkZ = floor(pos.z / CHUNK_BLOCK_SIZE);

    return glm::ivec3(ChunkX, ChunkY, ChunkZ);
}

/**
 * This function converts absolute `pos` to a relative block within a chunk position
 */
glm::ivec3 world::convertToChunkRelative(glm::ivec3 pos){
    pos.x %= CHUNK_BLOCK_SIZE;
    pos.y %= CHUNK_BLOCK_SIZE;
    pos.z %= CHUNK_BLOCK_SIZE;

    if(pos.x < 0){
        pos.x += CHUNK_BLOCK_SIZE;
    }

    if(pos.y < 0){
        pos.y += CHUNK_BLOCK_SIZE;
    }

    if(pos.z < 0){
        pos.z += CHUNK_BLOCK_SIZE;
    }
    return pos;
}

/**
 * This function stops all threads from the world
 */
void world::stop(){
    auto lock = std::unique_lock<std::mutex>(WorldGenMutex);
    WorldGenContinue = false;
    lock.unlock();
    WorldGenCond.notify_all();
}

void *world::WorldGenHelper(void* context){
    return ((world *) context)->WorldGen();
}

/**
 * Used for multithreading
 * This function will pick a chunk from queue of chunks to be generated
 * and then call generate function on it.
 * It will also cause nearby chunks to be marked to be recreated
 * The thread will continue as long as `world::WorldGenContinue` is true
 */
void *world::WorldGen(){
    while(WorldGenContinue){
        auto lock = std::unique_lock<std::mutex>(WorldGenMutex);
        WorldGenCond.wait(lock);
        if(!WorldGenQueue.empty()){
            chunk* c = WorldGenQueue.front();
            WorldGenQueue.pop_front();
            lock.unlock();
            c->generate();

            //we also would want to regenerate nearby chunks
            if(chunks[glm::ivec3(1,0,0) + c->pos] != NULL){
                chunks[glm::ivec3(1,0,0) + c->pos]->forceRecreate();
            }
            if(chunks[glm::ivec3(-1,0,0) + c->pos] != NULL){
                chunks[glm::ivec3(-1,0,0) + c->pos]->forceRecreate();
            }
            if(chunks[glm::ivec3(0,1,0) + c->pos] != NULL){
                chunks[glm::ivec3(0,1,0) + c->pos]->forceRecreate();
            }
            if(chunks[glm::ivec3(0,-1,0) + c->pos] != NULL){
                chunks[glm::ivec3(0,-1,0) + c->pos]->forceRecreate();
            }
            if(chunks[glm::ivec3(0,0,1) + c->pos] != NULL){
                chunks[glm::ivec3(0,0,1) + c->pos]->forceRecreate();
            }
            if(chunks[glm::ivec3(0,0,-1) + c->pos] != NULL){
                chunks[glm::ivec3(0,0,-1) + c->pos]->forceRecreate();
            }
        }
    }
    pthread_exit(NULL);
}