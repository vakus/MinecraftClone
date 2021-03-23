#include "../world/block.hpp"
#include "block_templates.cpp"

class BlockOakLeaves : public block
{
public:
    BlockOakLeaves(){
    }

    virtual bool isTransparent() override{
        return true;
    }

    GameObject3D getMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            BLOCK_STANDARD_VERTEX(6,0,6,0,6,0),
            {}
            };

        INCLUDE_BLOCK_STANDARD_INDICIES(FaceFlags, gameObject)
        return gameObject;
    }
};