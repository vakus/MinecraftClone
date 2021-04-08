#include "../world/block.hpp"
#include "block_templates.cpp"

class BlockSand : public block
{
public:
    BlockSand(){
    }

    virtual bool isTransparent() override{
        return false;
    }

    GameObject3D getMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            BLOCK_STANDARD_VERTEX(7,0,7,0,7,0),
            {}
        };

        INCLUDE_BLOCK_STANDARD_INDICIES(FaceFlags, gameObject)
        return gameObject;
    }
};