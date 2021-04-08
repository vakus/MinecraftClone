#ifndef CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../../blocks/BlockDirt.cpp"
#endif

#include "../../world/chunk.hpp"
#include "../../world/generators/generator.hpp"


TEST_CASE("Testing setting using XYZ and getting blocks using glm::ivec3", "[Chunk::SetBlock/GetBlock]"){

    //chunk depends on World
    World w = World();
    Chunk c = Chunk(glm::ivec3(0,0,0), &w);

    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                glm::ivec3 pos = glm::ivec3(x,y,z);

                c.SetBlock(pos, &blockDirt);

                REQUIRE(c.GetBlock(x,y,z) == &blockDirt);

                c.SetBlock(pos, NULL);

                REQUIRE(c.GetBlock(x,y,z) == NULL);
            }
        }
    }

    //required to stop all world threads
    w.Stop();
}

TEST_CASE("Testing setting and getting blocks using glm::ivec3", "[Chunk::SetBlock/GetBlock]"){

    //chunk depends on World
    World w = World();
    Chunk c = Chunk(glm::ivec3(0,0,0), &w);

    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                glm::ivec3 pos = glm::ivec3(x,y,z);

                c.SetBlock(pos, &blockDirt);

                REQUIRE(c.GetBlock(pos) == &blockDirt);

                c.SetBlock(pos, NULL);

                REQUIRE(c.GetBlock(pos) == NULL);
            }
        }
    }

    w.Stop();
}

TEST_CASE("Testing setting and getting blocks using XYZ", "[Chunk::SetBlock/GetBlock]"){

    //chunk depends on World
    World w = World();
    Chunk c = Chunk(glm::ivec3(0,0,0), &w);

    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                c.SetBlock(x,y,z, &blockDirt);

                REQUIRE(c.GetBlock(x,y,z) == &blockDirt);

                c.SetBlock(x,y,z, NULL);

                REQUIRE(c.GetBlock(x,y,z) == NULL);
            }
        }
    }

    w.Stop();
}

TEST_CASE("Testing setting using glm::ivec3 and getting blocks using XYZ", "[Chunk::SetBlock/GetBlock]"){

    //chunk depends on World
    World w = World();
    Chunk c = Chunk(glm::ivec3(0,0,0), &w);

    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                glm::ivec3 pos = glm::ivec3(x,y,z);

                c.SetBlock(x,y,z, &blockDirt);

                REQUIRE(c.GetBlock(pos) == &blockDirt);

                c.SetBlock(x,y,z, NULL);

                REQUIRE(c.GetBlock(pos) == NULL);
            }
        }
    }

    w.Stop();
}

class GeneratorTest: public Generator{
    public:
    void SetSeed(uint32_t seed){}
    uint32_t GetSeed(){return 0;}
    void Generate(std::vector<std::vector<std::vector<Block*>>> &blocks,
                  glm::ivec3 chunkPos){
        for(int x = 0; x < CHUNK_BLOCK_SIZE; x++){
            for(int y = 0; y < CHUNK_BLOCK_SIZE; y++){
                for(int z = 0; z < CHUNK_BLOCK_SIZE; z++){
                    blocks[x][y][z] = b;
                }
            }
        }
    }
    Block* b;
};

TEST_CASE("Testing Chunk generation", "[Chunk::Generate]"){
    World w = World();
    w.worldGenerator = new GeneratorTest();
    Chunk c = Chunk(glm::ivec3(0,0,0), &w);

    
    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    static_cast<GeneratorTest*>(w.worldGenerator)->b = &blockDirt;
    c.Generate();
    for(int x = 0; x < CHUNK_BLOCK_SIZE; x++){
        for(int y = 0; y < CHUNK_BLOCK_SIZE; y++){
            for(int z = 0; z < CHUNK_BLOCK_SIZE; z++){
                REQUIRE(
                    c.GetBlock(x,y,z)
                    == &blockDirt
                );
            }
        }
    }
    w.Stop();
}