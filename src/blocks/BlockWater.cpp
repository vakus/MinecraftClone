#include "../world/block.hpp"
#include "block_templates.cpp"

class BlockWater : public block
{
public:
    BlockWater(){
    }

    virtual bool isTransparent() override{
        return true;
    }

    GameObject3D getMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            BLOCK_STANDARD_VERTEX(0,2,0,2,0,2),
            {}
            };

        INCLUDE_BLOCK_STANDARD_INDICIES(FaceFlags, gameObject)
        return gameObject;
    }
};