#include "generator.hpp"
#include "../chunk.hpp"

class GeneratorFlat : public Generator{
public:
    void setSeed(uint32_t seed){
        this->seed = seed;
    }
    uint32_t getSeed(){
        return this->seed;
    }
    void generate(std::vector<std::vector<std::vector<block*>>> &blocks,
                  glm::ivec3 chunkPos){
        chunkPos *= CHUNK_BLOCK_SIZE;


        for(int x = 0; x < CHUNK_BLOCK_SIZE; x++){
            for(int z = 0; z < CHUNK_BLOCK_SIZE; z++){

                //terrain height
                int height = 8;
                
                for(int y = 0; y < CHUNK_BLOCK_SIZE; y++){
                    if(chunkPos.y + y < height - 3){
                        //stone
                        blocks[x][y][z] = BLOCKS[1];
                    }else if(chunkPos.y + y < height - 1){
                        //dirt
                        blocks[x][y][z] = BLOCKS[2];
                    }else if(chunkPos.y + y < height){
                        //grass block
                        blocks[x][y][z] = BLOCKS[0];
                    }
                }
            }
        }
    }
private:
    uint32_t seed;
};