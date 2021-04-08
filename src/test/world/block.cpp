#ifndef CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#endif

#include "../../world/block.hpp"

TEST_CASE("Testing GetTextureCoord from world/Block.cpp", "[GetTextureCoord]"){
    REQUIRE(
        GetTextureCoord(0,0, TextureCoordType::TOP_LEFT)
        == glm::vec2(0.0, 0.0)
    );
    REQUIRE(
        GetTextureCoord(0,0, TextureCoordType::TOP_RIGHT)
        == glm::vec2(0.1, 0.0)
    );
    REQUIRE(
        GetTextureCoord(0,0, TextureCoordType::BOTTOM_LEFT)
        == glm::vec2(0.0, 0.1)
    );
    REQUIRE(
        GetTextureCoord(0,0, TextureCoordType::BOTTOM_RIGHT)
        == glm::vec2(0.1, 0.1)
    );


    REQUIRE(
        GetTextureCoord(1,0, TextureCoordType::TOP_LEFT)
        == glm::vec2(0.1, 0.0)
    );
    REQUIRE(
        GetTextureCoord(1,0, TextureCoordType::TOP_RIGHT)
        == glm::vec2(0.2, 0.0)
    );
    REQUIRE(
        GetTextureCoord(1,0, TextureCoordType::BOTTOM_LEFT)
        == glm::vec2(0.1, 0.1)
    );
    REQUIRE(
        GetTextureCoord(1,0, TextureCoordType::BOTTOM_RIGHT)
        == glm::vec2(0.2, 0.1)
    );

    REQUIRE(
        GetTextureCoord(0, 1, TextureCoordType::TOP_LEFT)
        == glm::vec2(0.0, 0.1)
    );
    REQUIRE(
        GetTextureCoord(0, 1, TextureCoordType::TOP_RIGHT)
        == glm::vec2(0.1, 0.1)
    );
    REQUIRE(
        GetTextureCoord(0, 1, TextureCoordType::BOTTOM_LEFT)
        == glm::vec2(0.0, 0.2)
    );
    REQUIRE(
        GetTextureCoord(0, 1, TextureCoordType::BOTTOM_RIGHT)
        == glm::vec2(0.1, 0.2)
    );

    REQUIRE(
        GetTextureCoord(1, 1, TextureCoordType::TOP_LEFT)
        == glm::vec2(0.1, 0.1)
    );
    REQUIRE(
        GetTextureCoord(1, 1, TextureCoordType::TOP_RIGHT)
        == glm::vec2(0.2, 0.1)
    );
    REQUIRE(
        GetTextureCoord(1, 1, TextureCoordType::BOTTOM_LEFT)
        == glm::vec2(0.1, 0.2)
    );
    REQUIRE(
        GetTextureCoord(1, 1, TextureCoordType::BOTTOM_RIGHT)
        == glm::vec2(0.2, 0.2)
    );
    
}