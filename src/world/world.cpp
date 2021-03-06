#include "world.hpp"

#include <stdlib.h>
#include <chrono>

world::world(){
    seed = rand();
}

world::world(uint32_t wseed){
    seed = wseed;
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

    return c->getBlock(pos.x % CHUNK_BLOCK_WIDTH, pos.y % CHUNK_BLOCK_HEIGHT, pos.z % CHUNK_BLOCK_DEPTH);
}

block* world::getBlock(int x, int y, int z){
    return getBlock(glm::ivec3(x,y,z));
}

GameObject3D world::getMesh(glm::ivec3 pos, int distance){
    #ifdef PROFILE
    auto start = std::chrono::high_resolution_clock::now();
    #endif

    GameObject3D mesh;

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
                    c->generate(seed);
                    chunks[actualPos] = c;

                    //we also would want to regenerate nearby chunks
                    if(chunks[glm::ivec3(1,0,0) + actualPos] != NULL){
                        chunks[glm::ivec3(1,0,0) + actualPos]->forceRecreate();
                    }
                    if(chunks[glm::ivec3(-1,0,0) + actualPos] != NULL){
                        chunks[glm::ivec3(-1,0,0) + actualPos]->forceRecreate();
                    }
                    if(chunks[glm::ivec3(0,1,0) + actualPos] != NULL){
                        chunks[glm::ivec3(0,1,0) + actualPos]->forceRecreate();
                    }
                    if(chunks[glm::ivec3(0,-1,0) + actualPos] != NULL){
                        chunks[glm::ivec3(0,-1,0) + actualPos]->forceRecreate();
                    }
                    if(chunks[glm::ivec3(0,0,1) + actualPos] != NULL){
                        chunks[glm::ivec3(0,0,1) + actualPos]->forceRecreate();
                    }
                    if(chunks[glm::ivec3(0,0,-1) + actualPos] != NULL){
                        chunks[glm::ivec3(0,0,-1) + actualPos]->forceRecreate();
                    }
                }
                GameObject3D chunkMesh = c->getMesh();

                int verticiesOffset = mesh.verticies.size();
                for(size_t i = 0; i < chunkMesh.indicies.size(); i++){
                    mesh.indicies.push_back(chunkMesh.indicies[i] + verticiesOffset);
                }
                for(size_t i = 0; i < chunkMesh.verticies.size(); i++){
                    mesh.verticies.push_back(chunkMesh.verticies[i]);
                }
            }
        }
    }

    #ifdef PROFILE
    auto end = std::chrono::high_resolution_clock::now();
    logger::profile("world::getMesh() took " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));
    logger::profile("world::getMesh() has " + std::to_string(mesh.indicies.size()) + " indicies");
    logger::profile("world::getMesh() has " + std::to_string(mesh.verticies.size()) + " verticies");
    #endif
    return mesh;
}

glm::ivec3 world::convertToChunk(glm::ivec3 pos){
    if(pos.x % CHUNK_BLOCK_WIDTH < 0){
        pos.x -= CHUNK_BLOCK_WIDTH - 1;
    }
    if(pos.y % CHUNK_BLOCK_HEIGHT < 0){
        pos.y -= CHUNK_BLOCK_HEIGHT - 1;
    }
    if(pos.z % CHUNK_BLOCK_DEPTH < 0){
        pos.z -= CHUNK_BLOCK_DEPTH - 1;
    }

    int ChunkX = floor(pos.x / CHUNK_BLOCK_WIDTH);
    int ChunkY = floor(pos.y / CHUNK_BLOCK_HEIGHT);
    int ChunkZ = floor(pos.z / CHUNK_BLOCK_DEPTH);

    return glm::ivec3(ChunkX, ChunkY, ChunkZ);
}

glm::ivec3 world::convertToChunkRelative(glm::ivec3 pos){
    pos.x %= CHUNK_BLOCK_WIDTH;
    pos.y %= CHUNK_BLOCK_HEIGHT;
    pos.z %= CHUNK_BLOCK_DEPTH;

    if(pos.x < 0){
        pos.x += CHUNK_BLOCK_WIDTH;
    }

    if(pos.y < 0){
        pos.y += CHUNK_BLOCK_HEIGHT;
    }

    if(pos.z < 0){
        pos.z += CHUNK_BLOCK_DEPTH;
    }

}