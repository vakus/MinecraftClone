#include "../world/block.hpp"
#include "block_templates.cpp"

class BlockStone : public Block
{
public:
    BlockStone(){
    }

    virtual bool IsTransparent() override{
        return false;
    }

    GameObject3D GetMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            BLOCK_STANDARD_VERTEX(1,0,1,0,1,0),
            {}
            };

        INCLUDE_BLOCK_STANDARD_INDICIES(FaceFlags, gameObject)
        return gameObject;
    }
};