#include "world.hpp"

#include <stdlib.h>
#include <chrono>
#include <algorithm>

#include "generators/generator_default.cpp"

world::world(){
    seed = rand();
    worldGenThread.resize(WORLDGEN_THREAD_COUNT_MAX);
    for(size_t x = 0; x < WORLDGEN_THREAD_COUNT_MAX; x++){
        pthread_create(&worldGenThread[x], NULL, &world::WorldGenHelper, this);
    }
    worldGenerator = new GeneratorDefault();
    worldGenerator->setSeed(seed);
}

world::world(uint32_t wseed){
    seed = wseed;
    worldGenThread.resize(WORLDGEN_THREAD_COUNT_MAX);
    for(size_t x = 0; x < WORLDGEN_THREAD_COUNT_MAX; x++){
        pthread_create(&worldGenThread[x], NULL, &world::WorldGenHelper, this);
    }
    worldGenerator = new GeneratorDefault();
    worldGenerator->setSeed(seed);
}

world::world(uint32_t wseed, Generator* wworldGenerator){
    seed = wseed;
    worldGenThread.resize(WORLDGEN_THREAD_COUNT_MAX);
    for(size_t x = 0; x < WORLDGEN_THREAD_COUNT_MAX; x++){
        pthread_create(&worldGenThread[x], NULL, &world::WorldGenHelper, this);
    }
    worldGenerator = wworldGenerator;
    worldGenerator->setSeed(seed);
}

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

void world::setBlock(int x, int y, int z, block* block){
    world::setBlock(glm::ivec3(x, y, z), block);
}

block* world::getBlock(glm::ivec3 pos){
    glm::ivec3 chunkPos = convertToChunk(pos);

    chunk* c = chunks[chunkPos];

    if(c == NULL){
        //if the chunk doesnt exist we dont want to generate it (could cause cascading generation)
        return NULL;
    }

    return c->getBlock(pos.x % CHUNK_BLOCK_SIZE, pos.y % CHUNK_BLOCK_SIZE, pos.z % CHUNK_BLOCK_SIZE);
}

block* world::getBlock(int x, int y, int z){
    return getBlock(glm::ivec3(x,y,z));
}

//this function sometimes segfaults on app start :(
GameObject3D world::getMesh(glm::ivec3 pos, int distance){
    #ifdef PROFILE
    auto start = std::chrono::high_resolution_clock::now();
    #endif

    GameObject3D mesh;
    GameObject3D translucentMesh;

    glm::ivec3 targetChunk = glm::ivec3(pos/16);

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

                int verticiesOffset = mesh.verticies.size();
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
    uint offset = mesh.verticies.size();
    mesh.verticies.insert(mesh.verticies.end(), {
             {pos, {0,0}, {0,0,0}},
             {pos, {0,0}, {0,0,0}},
             {pos, {0,0}, {0,0,0}},
    });
    mesh.indicies.insert(mesh.indicies.end(), {
        offset, offset+1, offset+2
    });

    #ifdef PROFILE
    auto end = std::chrono::high_resolution_clock::now();
    logger::profile("world::getMesh() took " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));
    logger::profile("world::getMesh() has " + std::to_string(mesh.indicies.size()) + " indicies");
    logger::profile("world::getMesh() has " + std::to_string(mesh.verticies.size()) + " verticies");
    #endif
    return mesh;
}

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

void world::stop(){
    auto lock = std::unique_lock<std::mutex>(WorldGenMutex);
    WorldGenContinue = false;
    lock.unlock();
    WorldGenCond.notify_all();
}

void *world::WorldGenHelper(void* context){
    return ((world *) context)->WorldGen();
}

void *world::WorldGen(){
    while(WorldGenContinue){
        auto lock = std::unique_lock<std::mutex>(WorldGenMutex);
        WorldGenCond.wait(lock);
        if(!WorldGenQueue.empty()){
            chunk* c = WorldGenQueue.front();
            WorldGenQueue.pop_front();
            lock.unlock();
            //seed should not suffer from concurrency
            //as it *should* only be changed before world is created
            c->generate();
            c->forceRecreate();

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