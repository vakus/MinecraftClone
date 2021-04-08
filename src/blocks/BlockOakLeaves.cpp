#include "../world/block.hpp"
#include "block_templates.cpp"

class BlockOakLeaves : public Block
{
public:
    BlockOakLeaves(){
    }

    virtual bool IsTransparent() override{
        return true;
    }

    GameObject3D GetMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            BLOCK_STANDARD_VERTEX(6,0,6,0,6,0),
            {}
            };

        INCLUDE_BLOCK_STANDARD_INDICIES(FaceFlags, gameObject)
        return gameObject;
    }
};