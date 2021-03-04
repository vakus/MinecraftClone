#include "../world/block.hpp"

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
            {/*back*/
             {{0.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_TOP},
             {{1.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_TOP},
             {{1.0f, 1.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_TOP},
             {{0.0f, 1.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_TOP},
             /*bottom*/
             {{0.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE},
             {{1.0f, 0.0f, 1.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE},
             {{0.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE},
             {{1.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE},
             /*top*/
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
             /*front*/
             {{0.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_BOTTOM},
             {{1.0f, 0.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_BOTTOM},
             {{1.0f, 1.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_BOTTOM},
             {{0.0f, 1.0f, 0.0f}, getTextureCoord(1, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_BOTTOM}},
            {}};
            
        if((FaceFlags & BlockFace::BACK) == BlockFace::BACK){
            gameObject.indicies.insert(gameObject.indicies.end(), {0, 1, 3, 1, 2, 3});
        }
        if((FaceFlags & BlockFace::BOTTOM) == BlockFace::BOTTOM){
            gameObject.indicies.insert(gameObject.indicies.end(), {6, 5, 4, 6, 7, 5});
        }
        if((FaceFlags & BlockFace::TOP) == BlockFace::TOP){
            gameObject.indicies.insert(gameObject.indicies.end(), {11, 10, 9, 10, 8, 9});
        }
        if((FaceFlags & BlockFace::LEFT) == BlockFace::LEFT){
            gameObject.indicies.insert(gameObject.indicies.end(), {14, 13, 12, 14, 15, 13});
        }
        if((FaceFlags & BlockFace::RIGHT) == BlockFace::RIGHT){
            gameObject.indicies.insert(gameObject.indicies.end(), {16, 17, 18, 17, 19, 18});
        }
        if((FaceFlags & BlockFace::FRONT) == BlockFace::FRONT){
            gameObject.indicies.insert(gameObject.indicies.end(), {20, 22, 21, 23, 22, 20});
        }
        return gameObject;
    }
};