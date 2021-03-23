#ifndef CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../../blocks/BlockDirt.cpp"
#endif

#include "../../world/chunk.hpp"
#include "../../world/generators/generator.hpp"


TEST_CASE("Testing setting using XYZ and getting blocks using glm::ivec3", "[chunk::setBlock/getBlock]"){

    //chunk depends on World
    world w = world();
    chunk c = chunk(glm::ivec3(0,0,0), &w);

    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                glm::ivec3 pos = glm::ivec3(x,y,z);

                c.setBlock(pos, &blockDirt);

                REQUIRE(c.getBlock(x,y,z) == &blockDirt);

                c.setBlock(pos, NULL);

                REQUIRE(c.getBlock(x,y,z) == NULL);
            }
        }
    }

    //required to stop all world threads
    w.stop();
}

TEST_CASE("Testing setting and getting blocks using glm::ivec3", "[chunk::setBlock/getBlock]"){

    //chunk depends on World
    world w = world();
    chunk c = chunk(glm::ivec3(0,0,0), &w);

    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                glm::ivec3 pos = glm::ivec3(x,y,z);

                c.setBlock(pos, &blockDirt);

                REQUIRE(c.getBlock(pos) == &blockDirt);

                c.setBlock(pos, NULL);

                REQUIRE(c.getBlock(pos) == NULL);
            }
        }
    }

    w.stop();
}

TEST_CASE("Testing setting and getting blocks using XYZ", "[chunk::setBlock/getBlock]"){

    //chunk depends on World
    world w = world();
    chunk c = chunk(glm::ivec3(0,0,0), &w);

    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                c.setBlock(x,y,z, &blockDirt);

                REQUIRE(c.getBlock(x,y,z) == &blockDirt);

                c.setBlock(x,y,z, NULL);

                REQUIRE(c.getBlock(x,y,z) == NULL);
            }
        }
    }

    w.stop();
}

TEST_CASE("Testing setting using glm::ivec3 and getting blocks using XYZ", "[chunk::setBlock/getBlock]"){

    //chunk depends on World
    world w = world();
    chunk c = chunk(glm::ivec3(0,0,0), &w);

    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                glm::ivec3 pos = glm::ivec3(x,y,z);

                c.setBlock(x,y,z, &blockDirt);

                REQUIRE(c.getBlock(pos) == &blockDirt);

                c.setBlock(x,y,z, NULL);

                REQUIRE(c.getBlock(pos) == NULL);
            }
        }
    }

    w.stop();
}

class GeneratorTest: public Generator{
    public:
    void setSeed(uint32_t seed){}
    uint32_t getSeed(){return 0;}
    void generate(std::vector<std::vector<std::vector<block*>>> &blocks,
                  glm::ivec3 chunkPos){
        for(int x = 0; x < CHUNK_BLOCK_SIZE; x++){
            for(int y = 0; y < CHUNK_BLOCK_SIZE; y++){
                for(int z = 0; z < CHUNK_BLOCK_SIZE; z++){
                    blocks[x][y][z] = b;
                }
            }
        }
    }
    block* b;
};

TEST_CASE("Testing chunk generation", "[chunk::generate]"){
    world w = world();
    w.worldGenerator = new GeneratorTest();
    chunk c = chunk(glm::ivec3(0,0,0), &w);

    
    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    static_cast<GeneratorTest*>(w.worldGenerator)->b = &blockDirt;
    c.generate();
    for(int x = 0; x < CHUNK_BLOCK_SIZE; x++){
        for(int y = 0; y < CHUNK_BLOCK_SIZE; y++){
            for(int z = 0; z < CHUNK_BLOCK_SIZE; z++){
                REQUIRE(
                    c.getBlock(x,y,z)
                    == &blockDirt
                );
            }
        }
    }
    w.stop();
}