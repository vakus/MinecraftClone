#include "generator.hpp"
#include "../chunk.hpp"

/**
 * This generator simply creates flat terrain
 */
class GeneratorFlat : public Generator{
public:
    void SetSeed(uint32_t seed){
        this->seed = seed;
    }
    uint32_t GetSeed(){
        return this->seed;
    }
    /**
     * Generates flat terrain up to absolute block height of 8
     * Top layer is grass block, 2 layers below are dirt, rest down to absolute 0 is stone
     */
    void Generate(std::vector<std::vector<std::vector<Block*>>> &blocks,
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
                    }else if(chunkPos.y + y < height - 2){
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