#include "../world/block.hpp"
#include "block_templates.cpp"

class BlockStone : public block
{
public:
    BlockStone(){
    }

    virtual int getId() override{
        return 2;
    }

    virtual bool isTransparent() override{
        return false;
    }

    GameObject3D getMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            BLOCK_STANDARD_VERTEX(1,0),
            {}
            };

        BLOCK_STANDARD_INDICIES(FaceFlags, gameObject)
        return gameObject;
    }
};