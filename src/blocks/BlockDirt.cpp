#include "../world/block.hpp"
#include "block_templates.cpp"

class BlockDirt : public Block
{
public:
    BlockDirt(){
    }

    virtual bool IsTransparent() override{
        return false;
    }

    GameObject3D GetMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            BLOCK_STANDARD_VERTEX(3,0,3,0,3,0),
            {}
        };

        INCLUDE_BLOCK_STANDARD_INDICIES(FaceFlags, gameObject)
        return gameObject;
    }
};