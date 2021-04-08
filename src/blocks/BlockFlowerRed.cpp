#include "../world/block.hpp"
#include "block_templates.cpp"

class BlockFlowerRed : public Block
{
public:
    BlockFlowerRed(){
    }

    virtual bool IsTransparent() override{
        return true;
    }

    GameObject3D GetMesh(__attribute__((unused)) int FaceFlags) override
    {
        GameObject3D gameObject{
            BLOCK_FLOWER_VERTEX(1,1),
            BLOCK_FLOWER_INDICIES
            };
        //flowers should not optimise faces away,
        //either they will always be visible or they will not be called
        return gameObject;
    }
};