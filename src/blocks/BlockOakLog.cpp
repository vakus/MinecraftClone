#include "../world/block.hpp"
#include "block_templates.cpp"

class BlockOakLog : public Block
{
public:
    BlockOakLog(){
    }

    virtual bool IsTransparent() override{
        return false;
    }

    GameObject3D GetMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            BLOCK_STANDARD_VERTEX(4,0,5,0,4,0),
            {}
            };

        INCLUDE_BLOCK_STANDARD_INDICIES(FaceFlags, gameObject)
        return gameObject;
    }
};