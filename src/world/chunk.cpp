#include "chunk.hpp"
#include "../logger.hpp"
#include <PerlinNoise/PerlinNoise.hpp>
#include <chrono>

bool isTransparent(block* block){
    return (block == NULL ? true : block->isTransparent());
}

chunk::chunk(glm::ivec3 position){
    pos = position;
    recreate = true;
    blocks.resize(CHUNK_BLOCK_WIDTH);
    for(size_t x = 0; x < CHUNK_BLOCK_WIDTH; x++){
        blocks[x].resize(CHUNK_BLOCK_HEIGHT);
        for(size_t y = 0; y < CHUNK_BLOCK_HEIGHT; y++){
            blocks[x][y].resize(CHUNK_BLOCK_DEPTH);
        }
    }
};

void chunk::setBlock(int x, int y, int z, block* b){
    recreate = true;
    blocks[x][y][z] = b;
};

block* chunk::getBlock(glm::ivec3 pos){
    return blocks[pos.x][pos.y][pos.z];
}

block* chunk::getBlock(int x, int y, int z){
    return getBlock(glm::ivec3(x, y, z));
}

GameObject3D chunk::getMesh(){
    auto start = std::chrono::high_resolution_clock::now();
    if(recreate){
        logger::fine("Regenerating mesh");
        recreate = false;
        cachedMesh.indicies.clear();
        cachedMesh.verticies.clear();

        for(size_t x = 0; x < blocks.size(); x++){
            for(size_t y = 0; y < blocks[x].size(); y++){
                for(size_t z = 0; z < blocks[x][y].size(); z++){
                    if(blocks[x][y][z] != NULL){
                        int VerticiesOffset = cachedMesh.verticies.size();

                        logger::finer("Creating Mesh [" + std::to_string(x) + "][" + std::to_string(y) + "][" + std::to_string(z) + "]");

                        int faces = 0;
                        if(y == 15 || isTransparent(blocks[x][y+1][z])){
                            faces |= BlockFace::TOP;
                        }
                        if(y == 0 || isTransparent(blocks[x][y-1][z])){
                            faces |= BlockFace::BOTTOM;
                        }
                        if(x == 15 || isTransparent(blocks[x+1][y][z])){
                            faces |= BlockFace::LEFT;
                        }
                        if(x == 0 || isTransparent(blocks[x-1][y][z])){
                            faces |= BlockFace::RIGHT;
                        }
                        if(z == 15 || isTransparent(blocks[x][y][z+1])){
                            faces |= BlockFace::BACK;
                        }
                        if(z == 0 || isTransparent(blocks[x][y][z-1])){
                            faces |= BlockFace::FRONT;
                        }


                        GameObject3D blockObject = blocks[x][y][z]->getMesh(faces);
                        logger::finer("Block ID: " + std::to_string(blocks[x][y][z]->getId()));

                        for(size_t i = 0; i < blockObject.verticies.size(); i++){
                            Vertex v = blockObject.verticies[i];
                            v.pos.x += x;
                            v.pos.y += y;
                            v.pos.z += z;
                            logger::finer("Block Verticies[" + std::to_string(i) + "]: X: " + std::to_string(v.pos.x) + " Y:" + std::to_string(v.pos.y) + " Z:" + std::to_string(v.pos.z));
                            cachedMesh.verticies.push_back(v);
                        }
                        for(size_t i = 0; i < blockObject.indicies.size(); i++){
                            logger::finer("Block indicie[" + std::to_string(i) + "]: " + std::to_string(blockObject.indicies[i] + VerticiesOffset));
                            cachedMesh.indicies.push_back((blockObject.indicies[i] + VerticiesOffset));
                        }
                    }
                }
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    //logger::profile("chunk::getMesh() took " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));
    return cachedMesh;
};

void chunk::generate(uint32_t seed){
    //for now only generate a single chunk
    if(pos.y < 0){
        return;
    }
    int chunkOffsetX = pos.x * 16;
    int chunkOffsetY = pos.y * 16;
    int chunkOffsetZ = pos.z * 16;

    const siv::PerlinNoise perlin(seed);

    for(int x = 0; x < CHUNK_BLOCK_WIDTH; x++){
        for(int z = 0; z < CHUNK_BLOCK_DEPTH; z++){

            //terrain height
            int height = (perlin.accumulatedOctaveNoise2D((float)(chunkOffsetX + x)/16, (float)(chunkOffsetZ + z)/16, CHUNK_GENERATION_OCTAVES) + 1.0f) * ((CHUNK_GENERATION_MAX_Y - CHUNK_GENERATION_MIN_Y) / 2);
            
            for(int y = 0; y < CHUNK_BLOCK_HEIGHT; y++){
                if(chunkOffsetY + y < height + CHUNK_GENERATION_MIN_Y -3){
                    blocks[x][y][z] = BLOCKS[1];
                }else if(chunkOffsetY + y < height + CHUNK_GENERATION_MIN_Y - 1){
                    blocks[x][y][z] = BLOCKS[2];
                }else if(chunkOffsetY + y < height + CHUNK_GENERATION_MIN_Y){
                    blocks[x][y][z] = BLOCKS[0];
                }else if(chunkOffsetY + y < CHUNK_GENERATION_SEA_LEVEL){
                    //add water here
                }
            }
        }
    }
}