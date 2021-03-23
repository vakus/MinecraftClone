#include "generator.hpp"
#include "../chunk.hpp"

#include <PerlinNoise/PerlinNoise.hpp>

class GeneratorDefault : public Generator{
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

        const siv::PerlinNoise perlin(seed);

        for(int x = 0; x < CHUNK_BLOCK_SIZE; x++){
            for(int z = 0; z < CHUNK_BLOCK_SIZE; z++){

                //terrain height
                int height = (perlin.accumulatedOctaveNoise2D((float)(chunkPos.x + x)/16,
                            (float)(chunkPos.z + z)/16,
                            CHUNK_GENERATION_OCTAVES) + 1.0f)
                            * ((CHUNK_GENERATION_MAX_Y - CHUNK_GENERATION_MIN_Y) / 2);
                
                for(int y = 0; y < CHUNK_BLOCK_SIZE; y++){
                    if(chunkPos.y + y < height + CHUNK_GENERATION_MIN_Y -3){
                        blocks[x][y][z] = BLOCKS[1];
                    }else if(chunkPos.y + y < height + CHUNK_GENERATION_MIN_Y - 1){
                        blocks[x][y][z] = BLOCKS[2];
                    }else if(chunkPos.y + y < height + CHUNK_GENERATION_MIN_Y){
                        if(chunkPos.y + y >= CHUNK_GENERATION_SEA_LEVEL - 1){
                            blocks[x][y][z] = BLOCKS[0];
                        }else{
                            blocks[x][y][z] = BLOCKS[2];
                        }
                    }else if(chunkPos.y + y < height + CHUNK_GENERATION_MIN_Y + 1 && chunkPos.y + y > CHUNK_GENERATION_SEA_LEVEL){
                        //random flowers / trees
                        //FIXME: current version only generates clumps of flowers
                        int result = rand() % 1000;
                        if(result >= 995){
                            for(int i = 0; i < 5; i++){
                                if(y+i < CHUNK_BLOCK_SIZE){
                                    blocks[x][y+i][z] = BLOCKS[4];
                                }
                                if(y+2 < CHUNK_BLOCK_SIZE){
                                    for(int xo = -2; xo <= 2; xo++){
                                        for(int zo = -2; zo <= 2; zo++){
                                            if(x+xo > 0 && x+xo < CHUNK_BLOCK_SIZE && z+zo > 0 && z+zo < CHUNK_BLOCK_SIZE && (xo!=0 || zo!=0)){
                                                blocks[x+xo][y+2][z+zo] = BLOCKS[5];
                                            }
                                        }
                                    }
                                }

                                if(y+3 < CHUNK_BLOCK_SIZE){
                                    for(int xo = -2; xo <= 2; xo++){
                                        for(int zo = -2; zo <= 2; zo++){
                                            if(x+xo > 0 && x+xo < CHUNK_BLOCK_SIZE && z+zo > 0 && z+zo < CHUNK_BLOCK_SIZE && (xo!=0 || zo!=0)){
                                                blocks[x+xo][y+3][z+zo] = BLOCKS[5];
                                            }
                                        }
                                    }
                                }

                                if(y+4 < CHUNK_BLOCK_SIZE){
                                    for(int xo = -1; xo <= 1; xo++){
                                        for(int zo = -1; zo <= 1; zo++){
                                            if(x+xo > 0 && x+xo < CHUNK_BLOCK_SIZE && z+zo > 0 && z+zo < CHUNK_BLOCK_SIZE && (xo!=0 || zo!=0)){
                                                blocks[x+xo][y+4][z+zo] = BLOCKS[5];
                                            }
                                        }
                                    }
                                }
                            }
                        }else if(result >= 990){
                            blocks[x][y][z] = BLOCKS[3];
                        }
                    }else if(chunkPos.y + y < CHUNK_GENERATION_SEA_LEVEL){
                        blocks[x][y][z] = BLOCKS[6];
                    }
                }
            }
        }
    }
private:
    uint32_t seed;
};