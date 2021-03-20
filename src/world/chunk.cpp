#include "chunk.hpp"
#include "../logger.hpp"
#include <PerlinNoise/PerlinNoise.hpp>
#include <chrono>

bool isTransparent(block* block){
    return (block == NULL ? true : block->isTransparent());
}

chunk::chunk(glm::ivec3 position, world* w) : pos(position){
    worldo = w;
    recreate = true;
    generated = false;
    blocks.resize(CHUNK_BLOCK_SIZE);
    for(size_t x = 0; x < CHUNK_BLOCK_SIZE; x++){
        blocks[x].resize(CHUNK_BLOCK_SIZE);
        for(size_t y = 0; y < CHUNK_BLOCK_SIZE; y++){
            blocks[x][y].resize(CHUNK_BLOCK_SIZE, NULL);
        }
    }
};

void chunk::setBlock(glm::ivec3 bpos, block* b){
    recreate = true;
    blocks[bpos.x][bpos.y][bpos.z] = b;
}

void chunk::setBlock(int x, int y, int z, block* b){
    setBlock(glm::ivec3(x,y,z), b);
};

block* chunk::getBlock(glm::ivec3 pos){
    if(pos.x < 0){
        pos.x += CHUNK_BLOCK_SIZE;
    }
    if(pos.y < 0){
        pos.y += CHUNK_BLOCK_SIZE;
    }
    if(pos.z < 0){
        pos.z += CHUNK_BLOCK_SIZE;
    }
    return blocks[pos.x][pos.y][pos.z];
}

block* chunk::getBlock(int x, int y, int z){
    return getBlock(glm::ivec3(x, y, z));
}

GameObject3D chunk::getMesh(){
    #ifdef PROFILE
    auto start = std::chrono::high_resolution_clock::now();
    #endif
    
    if(recreate){
        recreate = false;
        cachedMesh.indicies.clear();
        cachedMesh.verticies.clear();

        for(size_t x = 0; x < blocks.size(); x++){
            for(size_t y = 0; y < blocks[x].size(); y++){
                for(size_t z = 0; z < blocks[x][y].size(); z++){
                    if(blocks[x][y][z] != NULL){
                        int VerticiesOffset = cachedMesh.verticies.size();

                        glm::ivec3 absolutePosition = pos;
                        absolutePosition *= 16;
                        absolutePosition.x += x;
                        absolutePosition.y += y;
                        absolutePosition.z += z;

                        int faces = 0;
                        if(y == 15 && isTransparent(worldo->getBlock(glm::ivec3(0,1,0) + absolutePosition))){
                            faces |= BlockFace::TOP;
                        }else if(y != 15 && isTransparent(blocks[x][y+1][z])){
                            faces |= BlockFace::TOP;
                        }

                        if(y == 0 && isTransparent(worldo->getBlock(glm::ivec3(0,-1,0) + absolutePosition))){
                            faces |= BlockFace::BOTTOM;
                        }else if(y != 0 && isTransparent(blocks[x][y-1][z])){
                            faces |= BlockFace::BOTTOM;
                        }

                        if(x == 15 && isTransparent(worldo->getBlock(glm::ivec3(1,0,0) + absolutePosition))){
                            faces |= BlockFace::LEFT;
                        }else if(x != 15 && isTransparent(blocks[x+1][y][z])){
                            faces |= BlockFace::LEFT;
                        }

                        if(x == 0 &&  isTransparent(worldo->getBlock(glm::ivec3(-1,0,0) + absolutePosition))){
                            faces |= BlockFace::RIGHT;
                        }else if(x != 0 && isTransparent(blocks[x-1][y][z])){
                            faces |= BlockFace::RIGHT;
                        }

                        if(z == 15 && isTransparent(worldo->getBlock(glm::ivec3(0,0,1) + absolutePosition))){
                            faces |= BlockFace::BACK;
                        }else if(z != 15 && isTransparent(blocks[x][y][z+1])){
                            faces |= BlockFace::BACK;
                        }

                        if(z == 0 && isTransparent(worldo->getBlock(glm::ivec3(0,0,-1) + absolutePosition))){
                            faces |= BlockFace::FRONT;
                        }else if(z != 00 && isTransparent(blocks[x][y][z-1])){
                            faces |= BlockFace::FRONT;
                        }

                        //this block has no faces, dont bother
                        if(faces == 0){
                            continue;
                        }

                        GameObject3D blockObject = blocks[x][y][z]->getMesh(faces);

                        std::for_each(blockObject.verticies.begin(), blockObject.verticies.end(), [absolutePosition, this](Vertex &v){
                            v.pos+=absolutePosition;
                        });
                        cachedMesh.verticies.insert(cachedMesh.verticies.end(), blockObject.verticies.begin(), blockObject.verticies.end());


                        std::for_each(blockObject.indicies.begin(), blockObject.indicies.end(), [VerticiesOffset](uint32_t &x){ x += VerticiesOffset;});
                        cachedMesh.indicies.insert(cachedMesh.indicies.end(), blockObject.indicies.begin(), blockObject.indicies.end());
                    }
                }
            }
        }
    }
    #ifdef PROFILE
    auto end = std::chrono::high_resolution_clock::now();
    logger::profile("chunk::getMesh() took " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));
    #endif
    return cachedMesh;
};

void chunk::generate(){
    if(generated){
        return;
    }
    generated = true;
    if(pos.y < 0){
        return;
    }
    worldo->worldGenerator->generate(blocks, pos);
}

void chunk::forceRecreate(){
    recreate = true;
}