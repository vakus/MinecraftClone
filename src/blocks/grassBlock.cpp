#include "../world/block.hpp"

#include "block_templates.cpp"

class BlockGrass : public block
{
public:
    BlockGrass(){
    }

    virtual bool isTransparent() override{
        return false;
    }

    GameObject3D getMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            BLOCK_STANDARD_VERTEX(0,0,2,0,3,0),
            {}
            };

        INCLUDE_BLOCK_STANDARD_INDICIES(FaceFlags, gameObject)
        return gameObject;
    }
};