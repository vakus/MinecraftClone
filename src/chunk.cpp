#include "chunk.hpp"
#include "logger.hpp"

chunk::chunk(){
    blocks.resize(CHUNK_BLOCK_WIDTH);
    for(size_t x = 0; x < CHUNK_BLOCK_WIDTH; x++){
        blocks[x].resize(CHUNK_BLOCK_HEIGHT);
        for(size_t y = 0; y < CHUNK_BLOCK_HEIGHT; y++){
            blocks[x][y].resize(CHUNK_BLOCK_DEPTH);
        }
    }
};

GameObject3D chunk::getMesh(){
    GameObject3D gameObject{};

    for(size_t x = 0; x < blocks.size(); x++){
        for(size_t y = 0; y < blocks[x].size(); y++){
            for(size_t z = 0; z < blocks[x][y].size(); z++){
                if(blocks[x][y][z].id != 0){
                    int VerticiesOffset = gameObject.verticies.size();

                    logger::finer("Creating Mesh [" + std::to_string(x) + "][" + std::to_string(y) + "][" + std::to_string(z) + "]");

                    block b = blocks[x][y][z];

                    logger::finer("Block ID: " + std::to_string(b.id));

                    for(size_t i = 0; i < b.verticies.size(); i++){
                        Vertex v = b.verticies[i];
                        v.pos.x += z;
                        v.pos.y += x;
                        v.pos.z += y;
                        logger::finer("Block Verticies[" + std::to_string(i) + "]: X: " + std::to_string(v.pos.x) + " Y:" + std::to_string(v.pos.y) + " Z:" + std::to_string(v.pos.z));
                        gameObject.verticies.push_back(v);
                    }
                    for(size_t i = 0; i < b.indicies.size(); i++){
                        logger::finer("Block indicie[" + std::to_string(i) + "]: " + std::to_string(b.indicies[i] + VerticiesOffset));
                        gameObject.indicies.push_back((b.indicies[i] + VerticiesOffset));
                    }
                }
            }
        }
    }
    return gameObject;
}