#ifndef CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../../blocks/dirt.cpp"
#endif

#include "../../world/chunk.hpp"


TEST_CASE("Testing world/chunk.cpp", "[chunk]"){

    //chunk depends on World
    world w = world();
    chunk c = chunk(glm::ivec3(0,0,0), &w);

    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    SECTION("Testing setting and getting blocks using glm::ivec3"){

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
    }

    SECTION("Testing setting and getting blocks using XYZ"){
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
    }

    SECTION("Testing setting using XYZ and getting blocks using glm::ivec3"){
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
    }

    SECTION("Testing setting using glm::ivec3 and getting blocks using XYZ"){
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
    }
    //required to stop all world threads
    w.stop();
}