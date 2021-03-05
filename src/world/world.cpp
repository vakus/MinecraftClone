#include "world.hpp"

#include <stdlib.h>

world::world(){
    seed = rand();
}

world::world(uint32_t wseed){
    seed = wseed;
}

void world::setBlock(glm::ivec3 pos, block* block){
    int ChunkX = pos.x / CHUNK_BLOCK_WIDTH;
    int ChunkY = pos.y / CHUNK_BLOCK_HEIGHT;
    int ChunkZ = pos.z / CHUNK_BLOCK_DEPTH;

    glm::ivec3 chunkPos = glm::ivec3(ChunkX, ChunkY, ChunkZ);

    chunk* c = chunks[chunkPos];

    if(c == NULL){
        //if chunk doesnt exist simply create it
        c = new chunk(chunkPos);

        chunks[chunkPos] = c;
    }

    c->setBlock(pos.x % CHUNK_BLOCK_WIDTH, pos.y % CHUNK_BLOCK_HEIGHT, pos.z % CHUNK_BLOCK_DEPTH, block);
}

void world::setBlock(int x, int y, int z, block* block){
    world::setBlock(glm::ivec3(x, y, z), block);
}

GameObject3D world::getMesh(glm::ivec3 pos, int distance){

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
                logger::finer("Getting Chunk X: " + std::to_string(actualPos.x) + " Y: " + std::to_string(actualPos.y) + " Z: " + std::to_string(actualPos.z));

                chunk* c = chunks[actualPos];
                if(c == NULL){
                    logger::fine("Creating chunk");
                    c = new chunk(actualPos);
                    c->generate(seed);
                    chunks[actualPos] = c;
                }
                GameObject3D chunkMesh = c->getMesh();

                int verticiesOffset = mesh.verticies.size();
                for(size_t i = 0; i < chunkMesh.indicies.size(); i++){
                    mesh.indicies.push_back(chunkMesh.indicies[i] + verticiesOffset);
                }
                for(size_t i = 0; i < chunkMesh.verticies.size(); i++){

                    Vertex v = chunkMesh.verticies[i];
                    v.pos += actualPos * glm::ivec3(16, 16, 16);
                    mesh.verticies.push_back(v);
                }
            }
        }
    }

    return mesh;
}