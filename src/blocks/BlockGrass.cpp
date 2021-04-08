#include "../world/block.hpp"
#include "block_templates.cpp"

class BlockGrass : public Block
{
public:
    BlockGrass(){
    }

    virtual bool IsTransparent() override{
        return false;
    }

    GameObject3D GetMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            BLOCK_STANDARD_VERTEX(0,0,2,0,3,0),
            {}
            };

        INCLUDE_BLOCK_STANDARD_INDICIES(FaceFlags, gameObject)
        return gameObject;
    }
};