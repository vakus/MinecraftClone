#include "../world/block.hpp"

class BlockDirt : public block
{
public:
    BlockDirt(){
    }

    virtual int getId() override{
        return 1;
    }

    virtual bool isTransparent() override{
        return false;
    }

    GameObject3D getMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            {},
            {}
            };

        uint base = 0;
        if((FaceFlags & BlockFace::BACK) == BlockFace::BACK){
            // dont add base here; it always will be 0
            gameObject.verticies.insert(gameObject.verticies.end(), {
             {{0.0f, 0.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE},
             {{1.0f, 0.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE},
             {{1.0f, 1.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE},
             {{0.0f, 1.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE},
            });
            gameObject.indicies.insert(gameObject.indicies.end(), {0, 1, 3, 1, 2, 3});
            base += 4;
        }
        if((FaceFlags & BlockFace::BOTTOM) == BlockFace::BOTTOM){
            gameObject.verticies.insert(gameObject.verticies.end(), {
             {{0.0f, 0.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_BOTTOM},
             {{1.0f, 0.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_BOTTOM},
             {{0.0f, 0.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_BOTTOM},
             {{1.0f, 0.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_BOTTOM},
            });
            gameObject.indicies.insert(gameObject.indicies.end(), {
                base + 2,
                base + 1,
                base, // +0
                base + 2,
                base + 3,
                base + 1
            });
            base += 4;
        }
        if((FaceFlags & BlockFace::TOP) == BlockFace::TOP){
            gameObject.verticies.insert(gameObject.verticies.end(), {
             {{0.0f, 1.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_TOP},
             {{1.0f, 1.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_TOP},
             {{0.0f, 1.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_TOP},
             {{1.0f, 1.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_TOP},
            });
            gameObject.indicies.insert(gameObject.indicies.end(), {
                base + 3,
                base + 2,
                base + 1,
                base + 2,
                base, // +0
                base + 1
            });
            base += 4;
        }
        if((FaceFlags & BlockFace::LEFT) == BlockFace::LEFT){
            gameObject.verticies.insert(gameObject.verticies.end(), {
             {{1.0f, 0.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE},
             {{1.0f, 1.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE},
             {{1.0f, 0.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE},
             {{1.0f, 1.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE},
            });
            gameObject.indicies.insert(gameObject.indicies.end(), {
                base + 2,
                base + 1,
                base, // +0
                base + 2,
                base + 3,
                base + 1
            });
            base += 4;
        }
        if((FaceFlags & BlockFace::RIGHT) == BlockFace::RIGHT){
            gameObject.verticies.insert(gameObject.verticies.end(), {
             {{0.0f, 0.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE},
             {{0.0f, 1.0f, 1.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE},
             {{0.0f, 0.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE},
             {{0.0f, 1.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE},
            });
            gameObject.indicies.insert(gameObject.indicies.end(), {
                base, // +0
                base + 1,
                base + 2,
                base + 1,
                base + 3,
                base + 2
            });
            base += 4;
        }
        if((FaceFlags & BlockFace::FRONT) == BlockFace::FRONT){
            gameObject.verticies.insert(gameObject.verticies.end(), {
             {{0.0f, 0.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE},
             {{1.0f, 0.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE},
             {{1.0f, 1.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE},
             {{0.0f, 1.0f, 0.0f}, getTextureCoord(0, 0, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE}
            });
            gameObject.indicies.insert(gameObject.indicies.end(), {
                base, //+0
                base + 2,
                base + 1,
                base + 3,
                base + 2,
                base //+0
            });
        }
        return gameObject;
    }
};