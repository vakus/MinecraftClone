#include "../world/block.hpp"
#include "block_templates.cpp"

class BlockWater : public Block
{
public:
    BlockWater(){
    }

    virtual bool IsTransparent() override{
        return true;
    }

    GameObject3D GetMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            BLOCK_STANDARD_VERTEX(0,2,0,2,0,2),
            {}
            };

        INCLUDE_BLOCK_STANDARD_INDICIES(FaceFlags, gameObject)
        return gameObject;
    }
};