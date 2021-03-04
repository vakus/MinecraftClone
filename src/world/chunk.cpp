#include "chunk.hpp"
#include "../logger.hpp"

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

GameObject3D chunk::getMesh(){
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
                            faces |= BlockFace::BACK;
                        }
                        if(x == 0 || isTransparent(blocks[x-1][y][z])){
                            faces |= BlockFace::FRONT;
                        }
                        if(z == 15 || isTransparent(blocks[x][y][z+1])){
                            faces |= BlockFace::LEFT;
                        }
                        if(z == 0 || isTransparent(blocks[x][y][z-1])){
                            faces |= BlockFace::RIGHT;
                        }


                        GameObject3D blockObject = blocks[x][y][z]->getMesh(faces);
                        logger::finer("Block ID: " + std::to_string(blocks[x][y][z]->getId()));

                        for(size_t i = 0; i < blockObject.verticies.size(); i++){
                            Vertex v = blockObject.verticies[i];
                            v.pos.x += z;
                            v.pos.y += x;
                            v.pos.z = (v.pos.z + y) * -1;
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
    return cachedMesh;
};

void chunk::generate(){
    if(pos.y == 0){
        for(int x = 0; x < CHUNK_BLOCK_WIDTH; x++){
            for(int z = 0; z < CHUNK_BLOCK_DEPTH; z++){
                blocks[x][0][z] = block::BLOCKS[0];
            }
        }
    }
}