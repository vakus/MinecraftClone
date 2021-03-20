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
                        blocks[x][y][z] = BLOCKS[0];
                    }else if(chunkPos.y + y < height + CHUNK_GENERATION_MIN_Y + 1){
                        //random flowers
                        //FIXME: current version only generates clumps of flowers
                        if(perlin.accumulatedOctaveNoise3D(
                            (float)(chunkPos.x + x)/16,
                            (float)(chunkPos.y + y)/16,
                            (float)(chunkPos.z + z)/16,
                            CHUNK_GENERATION_OCTAVES) > 0.7f){
                            blocks[x][y][z] = BLOCKS[3];
                        }
                    }else if(chunkPos.y + y < CHUNK_GENERATION_SEA_LEVEL){
                        //add water here
                    }
                }
            }
        }
    }
private:
    uint32_t seed;
};