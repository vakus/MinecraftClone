#include "../block.hpp"

class BlockStone : public block
{
public:
    BlockStone(){
    }

    virtual int getId() override{
        return 2;
    }

    virtual bool isTransparent() override{
        return false;
    }

    GameObject3D getMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            {/*top*/
             {{0.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_TOP},
             {{1.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_TOP},
             {{1.0f, 1.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_TOP},
             {{0.0f, 1.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_TOP},
             /*front*/
             {{0.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE},
             {{1.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE},
             {{0.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE},
             {{1.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE},
             /*back*/
             {{0.0f, 1.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE},
             {{1.0f, 1.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE},
             {{0.0f, 1.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE},
             {{1.0f, 1.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE},
             /*left*/
             {{1.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE},
             {{1.0f, 1.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE},
             {{1.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE},
             {{1.0f, 1.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE},
             /*right*/
             {{0.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE},
             {{0.0f, 1.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE},
             {{0.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE},
             {{0.0f, 1.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE},
             /*bottom*/
             {{0.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_BOTTOM},
             {{1.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_BOTTOM},
             {{1.0f, 1.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_BOTTOM},
             {{0.0f, 1.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_BOTTOM}},
            {}};

        if((FaceFlags & BlockFace::TOP) == BlockFace::TOP){
            gameObject.indicies.insert(gameObject.indicies.end(), {2, 1, 0, 0, 3, 2});
        }
        if((FaceFlags & BlockFace::FRONT) == BlockFace::FRONT){
            gameObject.indicies.insert(gameObject.indicies.end(), {4, 5, 7, 7, 6, 4});
        }
        if((FaceFlags & BlockFace::BACK) == BlockFace::BACK){
            gameObject.indicies.insert(gameObject.indicies.end(), {11, 9, 8, 8, 10, 11});
        }
        if((FaceFlags & BlockFace::LEFT) == BlockFace::LEFT){
            gameObject.indicies.insert(gameObject.indicies.end(), {12, 13, 14, 13, 15, 14});
        }
        if((FaceFlags & BlockFace::RIGHT) == BlockFace::RIGHT){
            gameObject.indicies.insert(gameObject.indicies.end(), {18, 17, 16, 18, 19, 17});
        }
        if((FaceFlags & BlockFace::BOTTOM) == BlockFace::BOTTOM){
            gameObject.indicies.insert(gameObject.indicies.end(), {20, 21, 22, 22, 23, 20});
        }
        return gameObject;
    }
};