#ifndef CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../../blocks/BlockDirt.cpp"
#endif

#include "../../world/world.hpp"

TEST_CASE("Testing converting coordinates to Chunk Coordinate", "[World::ConvertToChunk]"){
    SECTION("Testing positive coordinates"){
        REQUIRE(
            World::ConvertToChunk(glm::ivec3(0,0,0))
            == glm::ivec3(0,0,0)
        );
        REQUIRE(
            World::ConvertToChunk(glm::ivec3(15,15,15))
            == glm::ivec3(0,0,0)
        );
        REQUIRE(
            World::ConvertToChunk(glm::ivec3(12, 4, 6))
            == glm::ivec3(0,0,0)
        );

        REQUIRE(
            World::ConvertToChunk(glm::ivec3(16,16,16))
            == glm::ivec3(1,1,1)
        );

        REQUIRE(
            World::ConvertToChunk(glm::ivec3(16, 0, 32))
            == glm::ivec3(1,0,2)
        );

        REQUIRE(
            World::ConvertToChunk(glm::ivec3(20, 10, 40))
            == glm::ivec3(1,0,2)
        );
    }

    SECTION("Testing negative coordinates"){
        REQUIRE(
            World::ConvertToChunk(glm::ivec3(-1,-1,-1))
            == glm::ivec3(-1,-1,-1)
        );

        REQUIRE(
            World::ConvertToChunk(glm::ivec3(-15,-15,-15))
            == glm::ivec3(-1, -1, -1)
        );

        REQUIRE(
            World::ConvertToChunk(glm::ivec3(-16, -16, -16))
            == glm::ivec3(-1,-1,-1)
        );

        REQUIRE(
            World::ConvertToChunk(glm::ivec3(-20, -10, -40))
            == glm::ivec3(-2, -1, -3)
        );

        REQUIRE(
            World::ConvertToChunk(glm::ivec3(-17,-17,-17))
            == glm::ivec3(-2,-2,-2)
        );
    }

    SECTION("Testing mixed coordinates"){
        REQUIRE(
            World::ConvertToChunk(glm::ivec3(-16, 0, 16))
            == glm::ivec3(-1, 0, 1)
        );

        REQUIRE(
            World::ConvertToChunk(glm::ivec3(-17, 33, 23))
            == glm::ivec3(-2, 2, 1)
        );
    }
}

TEST_CASE("Testing converting coordinates to Chunk Relative Coordinate", "[World::ConvertToChunkRelative]"){
    SECTION("Testing positive coordinates"){
        REQUIRE(
            World::ConvertToChunkRelative(glm::ivec3(0,0,0))
            == glm::ivec3(0,0,0)
        );

        REQUIRE(
            World::ConvertToChunkRelative(glm::ivec3(15,15,15))
            == glm::ivec3(15,15,15)
        );

        REQUIRE(
            World::ConvertToChunkRelative(glm::ivec3(16,16,16))
            == glm::ivec3(0,0,0)
        );

        REQUIRE(
            World::ConvertToChunkRelative(glm::ivec3(3, 7, 11))
            == glm::ivec3(3, 7, 11)
        );

        REQUIRE(
            World::ConvertToChunkRelative(glm::ivec3(3, 18, 37))
            == glm::ivec3(3, 2, 5)
        );
    }

    SECTION("Testing negative coordinates"){
        REQUIRE(
            World::ConvertToChunkRelative(glm::ivec3(-1,-1,-1))
            == glm::ivec3(15,15,15)
        );

        REQUIRE(
            World::ConvertToChunkRelative(glm::ivec3(-16,-16,-16))
            == glm::ivec3(0,0,0)
        );

        REQUIRE(
            World::ConvertToChunkRelative(glm::ivec3(-17,-17,-17))
            == glm::ivec3(15,15,15)
        );

        REQUIRE(
            World::ConvertToChunkRelative(glm::ivec3(-3, -7, -11))
            == glm::ivec3(13, 9, 5)
        );

        REQUIRE(
            World::ConvertToChunkRelative(glm::ivec3(-3,-18,-37))
            == glm::ivec3(13, 14, 11)
        );
    }

    SECTION("Testing mixed coordinates"){
        REQUIRE(
            World::ConvertToChunkRelative(glm::ivec3(-3, 0, 12))
            == glm::ivec3(13, 0, 12)
        );

        REQUIRE(
            World::ConvertToChunkRelative(glm::ivec3(0, -3, 12))
            == glm::ivec3(0, 13, 12)
        );

        REQUIRE(
            World::ConvertToChunkRelative(glm::ivec3(0, 12, -3))
            == glm::ivec3(0, 12, 13)
        );
    }
}

TEST_CASE("Testing SetBlock and GetBlock using glm::ivec3", "[World::GetBlock/SetBlock]"){
    World w = World();

    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                glm::ivec3 pos = glm::ivec3(x,y,z);

                w.SetBlock(pos, &blockDirt);

                REQUIRE(w.GetBlock(pos) == &blockDirt);

                w.SetBlock(pos, NULL);

                REQUIRE(w.GetBlock(pos) == NULL);
            }
        }
    }

    w.Stop();
}

TEST_CASE("Testing SetBlock and GetBlock using XYZ", "[World::GetBlock/SetBlock]"){
    World w = World();

    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){

                w.SetBlock(x,y,z, &blockDirt);

                REQUIRE(w.GetBlock(x,y,z) == &blockDirt);

                w.SetBlock(x,y,z, NULL);

                REQUIRE(w.GetBlock(x,y,z) == NULL);
            }
        }
    }

    w.Stop();
}

TEST_CASE("Testing SetBlock using glm::ivec3 and GetBlock using XYZ", "[World::GetBlock/SetBlock]"){
    World w = World();

    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                glm::ivec3 pos = glm::ivec3(x,y,z);

                w.SetBlock(pos, &blockDirt);

                REQUIRE(w.GetBlock(x,y,z) == &blockDirt);

                w.SetBlock(pos, NULL);

                REQUIRE(w.GetBlock(x,y,z) == NULL);
            }
        }
    }

    w.Stop();
}

TEST_CASE("Testing SetBlock using XYZ and GetBlock using glm::ivec3", "[World::GetBlock/SetBlock]"){
    World w = World();

    //blocks to be used for tests
    BlockDirt blockDirt = BlockDirt();

    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                glm::ivec3 pos = glm::ivec3(x,y,z);

                w.SetBlock(x,y,z, &blockDirt);

                REQUIRE(w.GetBlock(pos) == &blockDirt);

                w.SetBlock(x,y,z, NULL);

                REQUIRE(w.GetBlock(pos) == NULL);
            }
        }
    }

    w.Stop();
}