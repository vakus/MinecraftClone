#include "../world/block.hpp"
#include "block_templates.cpp"

#define BLOCK_SHADE_BLACK {0.0f,0.0f,0.0f}

class BlockDirt : public block
{
public:
    BlockDirt(){
    }

    virtual bool isTransparent() override{
        return false;
    }

    GameObject3D getMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            BLOCK_STANDARD_VERTEX(3,0,3,0,3,0),
            {}
        };

        INCLUDE_BLOCK_STANDARD_INDICIES(FaceFlags, gameObject)
        return gameObject;
    }
};