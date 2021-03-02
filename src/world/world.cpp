#include "world.hpp"

void world::setBlock(glm::ivec3 pos, block* block){
    int ChunkX = pos.x / CHUNK_BLOCK_WIDTH;
    int ChunkY = pos.y / CHUNK_BLOCK_HEIGHT;
    int ChunkZ = pos.z / CHUNK_BLOCK_DEPTH;

    chunk* c = chunks[glm::ivec3(ChunkX, ChunkY, ChunkZ)];

    if(c == NULL){
        //if chunk doesnt exist simply create it
        c = new chunk();
        chunks[glm::ivec3(ChunkX, ChunkY, ChunkZ)] = c;
        //chunks.insert(std::make_pair(glm::ivec3(ChunkX, ChunkY, ChunkZ), c));
    }

    c->setBlock(pos.x % CHUNK_BLOCK_WIDTH, pos.y % CHUNK_BLOCK_HEIGHT, pos.z % CHUNK_BLOCK_DEPTH, block);
}

void world::setBlock(int x, int y, int z, block* block){
    world::setBlock(glm::ivec3(x, y, z), block);
}

GameObject3D world::getMesh(glm::ivec3 pos, int distance){

    GameObject3D mesh;

    for(int x = -distance; x <= distance; x++){
        for(int y = -distance; y <= distance; y++){
            for(int z = -distance; z <= distance; z++){
                glm::ivec3 actualPos = glm::ivec3(pos/16);
                actualPos.x += x;
                actualPos.y += y;
                actualPos.z += z;

                logger::finer("Getting Chunk X: " + std::to_string(actualPos.x) + " Y: " + std::to_string(actualPos.y) + " Z: " + std::to_string(actualPos.z));

                chunk* c = chunks[actualPos];

                if(c != NULL){
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
    }

    return mesh;
}