#include "../world/block.hpp"
#include "block_templates.cpp"

class BlockOakLog : public block
{
public:
    BlockOakLog(){
    }

    virtual int getId() override{
        return 5;
    }

    virtual bool isTransparent() override{
        return false;
    }

    GameObject3D getMesh(int FaceFlags) override
    {
        GameObject3D gameObject{
            BLOCK_STANDARD_VERTEX(4,0,5,0,4,0),
            {}
            };

        INCLUDE_BLOCK_STANDARD_INDICIES(FaceFlags, gameObject)
        return gameObject;
    }
};