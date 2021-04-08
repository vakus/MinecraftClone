#include "chunk.hpp"
#include "../logger.hpp"
#include <PerlinNoise/PerlinNoise.hpp>
#include <chrono>

/**
 * checks if `current` block needs face when covered by `other`
 * if `current` and `other` are the same the face is not needed
 * otherwise
 *      if `other` is null the block will need face
 *      if `other` is transparent block will need face
 */
bool needsFace(block* other, block* current){
    return (other == current ? false : (other == NULL ? true : other->isTransparent()));
}

chunk::chunk(glm::ivec3 position, world* w) : pos(position){
    worldo = w;
    recreate = true;
    recreateTranslucent = true;
    generated = false;
    blocks.resize(CHUNK_BLOCK_SIZE);
    for(size_t x = 0; x < CHUNK_BLOCK_SIZE; x++){
        blocks[x].resize(CHUNK_BLOCK_SIZE);
        for(size_t y = 0; y < CHUNK_BLOCK_SIZE; y++){
            blocks[x][y].resize(CHUNK_BLOCK_SIZE, NULL);
        }
    }
};

/**
 * Sets block at `bpos` to block specified by pointer `b`
 * This will flag the mesh of a chunk to be recreated
 */
void chunk::setBlock(glm::ivec3 bpos, block* b){
    recreate = true;
    recreateTranslucent = true;
    blocks[bpos.x][bpos.y][bpos.z] = b;
}

/**
 * Sets block at xyz to block specified by pointer `b`
 * This will flag the mesh of a chunk to be recreated
 */
void chunk::setBlock(int x, int y, int z, block* b){
    setBlock(glm::ivec3(x,y,z), b);
};

/**
 * Returns pointer to block that is at `pos`
 * If either x/y/z is below 0 then size of chunk will be added to it to allow e.g. using -1 as alternative to 15
 * Note values outside range of -CHUNK_BLOCK_SIZE to CHUNK_BLOCK_SIZE will cause reading outside range of blocks
 */
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

/**
 * Returns pointer to block that is at xyz
 * If either x/y/z is below 0 then size of chunk will be added to it to allow e.g. using -1 as alternative to 15
 * Note values outside range of -CHUNK_BLOCK_SIZE to CHUNK_BLOCK_SIZE will cause reading outside range of blocks
 */
block* chunk::getBlock(int x, int y, int z){
    return getBlock(glm::ivec3(x, y, z));
}

/**
 * Returns the non-transparent mesh of a chunk
 * if `chunk::recreate` is set to true it will generate new mesh for chunk and cache it
 * otherwise it will return cached last response
 */
GameObject3D chunk::getMesh(){
    
    if(recreate){
        recreate = false;
        cachedMesh.indicies.clear();
        cachedMesh.verticies.clear();

        for(size_t x = 0; x < blocks.size(); x++){
            for(size_t y = 0; y < blocks[x].size(); y++){
                for(size_t z = 0; z < blocks[x][y].size(); z++){
                    if(blocks[x][y][z] != NULL && !(blocks[x][y][z]->isTransparent())){
                        int VerticiesOffset = cachedMesh.verticies.size();

                        glm::ivec3 absolutePosition = pos;
                        absolutePosition *= 16;
                        absolutePosition.x += x;
                        absolutePosition.y += y;
                        absolutePosition.z += z;

                        int faces = 0;
                        if(y == 15 && needsFace(worldo->getBlock(glm::ivec3(0,1,0) + absolutePosition), blocks[x][y][z])){
                            faces |= BlockFace::TOP;
                        }else if(y != 15 && needsFace(blocks[x][y+1][z], blocks[x][y][z])){
                            faces |= BlockFace::TOP;
                        }

                        if(y == 0 && needsFace(worldo->getBlock(glm::ivec3(0,-1,0) + absolutePosition), blocks[x][y][z])){
                            faces |= BlockFace::BOTTOM;
                        }else if(y != 0 && needsFace(blocks[x][y-1][z], blocks[x][y][z])){
                            faces |= BlockFace::BOTTOM;
                        }

                        if(x == 15 && needsFace(worldo->getBlock(glm::ivec3(1,0,0) + absolutePosition), blocks[x][y][z])){
                            faces |= BlockFace::LEFT;
                        }else if(x != 15 && needsFace(blocks[x+1][y][z], blocks[x][y][z])){
                            faces |= BlockFace::LEFT;
                        }

                        if(x == 0 &&  needsFace(worldo->getBlock(glm::ivec3(-1,0,0) + absolutePosition), blocks[x][y][z])){
                            faces |= BlockFace::RIGHT;
                        }else if(x != 0 && needsFace(blocks[x-1][y][z], blocks[x][y][z])){
                            faces |= BlockFace::RIGHT;
                        }

                        if(z == 15 && needsFace(worldo->getBlock(glm::ivec3(0,0,1) + absolutePosition), blocks[x][y][z])){
                            faces |= BlockFace::BACK;
                        }else if(z != 15 && needsFace(blocks[x][y][z+1], blocks[x][y][z])){
                            faces |= BlockFace::BACK;
                        }

                        if(z == 0 && needsFace(worldo->getBlock(glm::ivec3(0,0,-1) + absolutePosition), blocks[x][y][z])){
                            faces |= BlockFace::FRONT;
                        }else if(z != 0 && needsFace(blocks[x][y][z-1], blocks[x][y][z])){
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
    return cachedMesh;
};

/**
 * Returns the transparent mesh of a chunk
 * if `chunk::recreateTranslucent` is set to true it will generate new mesh for chunk and cache it
 * otherwise it will return cached last response
 */
GameObject3D chunk::getTranslucentMesh(){
    
    if(recreateTranslucent){
        recreateTranslucent = false;
        cachedTranslucentMesh.indicies.clear();
        cachedTranslucentMesh.verticies.clear();

        for(size_t x = 0; x < blocks.size(); x++){
            for(size_t y = 0; y < blocks[x].size(); y++){
                for(size_t z = 0; z < blocks[x][y].size(); z++){
                    if(blocks[x][y][z] != NULL && blocks[x][y][z]->isTransparent()){
                        int VerticiesOffset = cachedTranslucentMesh.verticies.size();

                        glm::ivec3 absolutePosition = pos;
                        absolutePosition *= 16;
                        absolutePosition.x += x;
                        absolutePosition.y += y;
                        absolutePosition.z += z;

                        int faces = 0;
                        if(y == 15 && needsFace(worldo->getBlock(glm::ivec3(0,1,0) + absolutePosition), blocks[x][y][z])){
                            faces |= BlockFace::TOP;
                        }else if(y != 15 && needsFace(blocks[x][y+1][z], blocks[x][y][z])){
                            faces |= BlockFace::TOP;
                        }

                        if(y == 0 && needsFace(worldo->getBlock(glm::ivec3(0,-1,0) + absolutePosition), blocks[x][y][z])){
                            faces |= BlockFace::BOTTOM;
                        }else if(y != 0 && needsFace(blocks[x][y-1][z], blocks[x][y][z])){
                            faces |= BlockFace::BOTTOM;
                        }

                        if(x == 15 && needsFace(worldo->getBlock(glm::ivec3(1,0,0) + absolutePosition), blocks[x][y][z])){
                            faces |= BlockFace::LEFT;
                        }else if(x != 15 && needsFace(blocks[x+1][y][z], blocks[x][y][z])){
                            faces |= BlockFace::LEFT;
                        }

                        if(x == 0 &&  needsFace(worldo->getBlock(glm::ivec3(-1,0,0) + absolutePosition), blocks[x][y][z])){
                            faces |= BlockFace::RIGHT;
                        }else if(x != 0 && needsFace(blocks[x-1][y][z], blocks[x][y][z])){
                            faces |= BlockFace::RIGHT;
                        }

                        if(z == 15 && needsFace(worldo->getBlock(glm::ivec3(0,0,1) + absolutePosition), blocks[x][y][z])){
                            faces |= BlockFace::BACK;
                        }else if(z != 15 && needsFace(blocks[x][y][z+1], blocks[x][y][z])){
                            faces |= BlockFace::BACK;
                        }

                        if(z == 0 && needsFace(worldo->getBlock(glm::ivec3(0,0,-1) + absolutePosition), blocks[x][y][z])){
                            faces |= BlockFace::FRONT;
                        }else if(z != 0 && needsFace(blocks[x][y][z-1], blocks[x][y][z])){
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
                        cachedTranslucentMesh.verticies.insert(cachedTranslucentMesh.verticies.end(), blockObject.verticies.begin(), blockObject.verticies.end());


                        std::for_each(blockObject.indicies.begin(), blockObject.indicies.end(), [VerticiesOffset](uint32_t &x){ x += VerticiesOffset;});
                        cachedTranslucentMesh.indicies.insert(cachedTranslucentMesh.indicies.end(), blockObject.indicies.begin(), blockObject.indicies.end());
                    }
                }
            }
        }
    }
    return cachedTranslucentMesh;
};

/**
 * This function requests that the chunk generates terrain
 * If chunk has already been generated this function will return instantly
 * If chunk is below y 0 then the chunk will not be generated
 * After terrain is generated, mesh is forced to be recreated
 */
void chunk::generate(){
    if(generated){
        return;
    }
    generated = true;
    if(pos.y < 0){
        return;
    }
    worldo->worldGenerator->generate(blocks, pos);
    forceRecreate();
}

/**
 * Marks mesh transparent and non-transparent mesh to be recreated
 */
void chunk::forceRecreate(){
    recreate = true;
    recreateTranslucent = true;
}