#include "generator.hpp"
#include "../chunk.hpp"

#include <PerlinNoise/PerlinNoise.hpp>

class GeneratorDefault : public Generator{
public:
    GeneratorDefault(world* w){
        worldo = w;
    }
    void setSeed(uint32_t seed){
        this->seed = seed;
    }
    uint32_t getSeed(){
        return this->seed;
    }
    void generate(std::vector<std::vector<std::vector<block*>>> &blocks,
                  glm::ivec3 chunkPos){
        glm::ivec3 absoluteBlockPos = chunkPos * CHUNK_BLOCK_SIZE;

        const siv::PerlinNoise perlin(seed);

        for(int x = 0; x < CHUNK_BLOCK_SIZE; x++){
            for(int z = 0; z < CHUNK_BLOCK_SIZE; z++){

                //terrain height at x/z
                int height = (perlin.accumulatedOctaveNoise2D((float)(absoluteBlockPos.x + x)/16,
                            (float)(absoluteBlockPos.z + z)/16,
                            CHUNK_GENERATION_OCTAVES) + 1.0f)
                            * ((CHUNK_GENERATION_MAX_Y - CHUNK_GENERATION_MIN_Y) / 2);
                
                for(int y = 0; y < CHUNK_BLOCK_SIZE; y++){
                    if(absoluteBlockPos.y + y < height + CHUNK_GENERATION_MIN_Y -3){
                        blocks[x][y][z] = BLOCKS[1];
                    }else if(absoluteBlockPos.y + y < height + CHUNK_GENERATION_MIN_Y - 1){
                        if(height + CHUNK_GENERATION_MIN_Y < CHUNK_GENERATION_SEA_LEVEL + 1){
                            blocks[x][y][z] = BLOCKS[8];
                        }else{
                            blocks[x][y][z] = BLOCKS[2];
                        }
                    }else if(absoluteBlockPos.y + y < height + CHUNK_GENERATION_MIN_Y){
                        if(absoluteBlockPos.y + y >= CHUNK_GENERATION_SEA_LEVEL){
                            blocks[x][y][z] = BLOCKS[0];
                        }else{
                            blocks[x][y][z] = BLOCKS[8];
                        }
                    }else if(absoluteBlockPos.y + y < height + CHUNK_GENERATION_MIN_Y + 1 && absoluteBlockPos.y + y > CHUNK_GENERATION_SEA_LEVEL){
                        //random flowers / trees
                        //FIXME: current version only generates clumps of flowers
                        int result = rand() % 1000;
                        if(result >= 995){
                            for(int yo = 2; yo < 4; yo++){
                                for(int xo = -2; xo <= 2; xo++){
                                    for(int zo = -2; zo <= 2; zo++){
                                        setBlock(blocks, chunkPos, glm::ivec3(x+xo,y+yo,z+zo) + absoluteBlockPos, BLOCKS[5]);
                                    }
                                }
                            }
                            for(int yo = 4; yo < 6; yo++){
                                for(int xo = -1; xo <= 1; xo++){
                                    for(int zo = -1; zo <= 1; zo++){
                                        setBlock(blocks, chunkPos, glm::ivec3(x+xo,y+yo,z+zo) + absoluteBlockPos, BLOCKS[5]);
                                    }
                                }
                            }
                            for(int i = 0; i < 5; i++){
                                if(y+i < CHUNK_BLOCK_SIZE){
                                    blocks[x][y+i][z] = BLOCKS[4];
                                }
                            }
                        }else if(result >= 992){
                            //yellow flower
                            blocks[x][y][z] = BLOCKS[3];
                        }else if(result >= 990){
                            //red flower
                            blocks[x][y][z] = BLOCKS[7];
                        }
                    }else if(absoluteBlockPos.y + y < CHUNK_GENERATION_SEA_LEVEL){
                        blocks[x][y][z] = BLOCKS[6];
                    }
                }
            }
        }
    }
private:
    uint32_t seed;
    world* worldo;

    /**
     * This function is a helper function to set block in either
     * currently edited chunk or outside it.
     * It's preferred to not be used if the block set is guaranteed to be within chunk
     * If the block set is not guaranteed to be within chunk, this function should be used
     * valid use example: setting blocks for tree (entire tree is one structure and parts of it may be outside border)
     * invalid use example: setting single block at X/Y/Z within chunk
     */
    void setBlock(std::vector<std::vector<std::vector<block*>>> &blocks,
                  glm::ivec3 chunkPos,
                  glm::ivec3 absolutePos,
                  block* bloc){
        if(world::convertToChunk(absolutePos) == chunkPos){
            glm::ivec3 relativeBlock = world::convertToChunkRelative(absolutePos);
            blocks[relativeBlock.x][relativeBlock.y][relativeBlock.z] = bloc;
        }else{
            worldo->setBlock(absolutePos, bloc);
        }
    }
};