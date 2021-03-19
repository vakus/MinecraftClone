
/**
 * This defines optimised list of vertecies to be used in a block
 * WARNING: this list only works if all faces have the same texture
 * This will work e.g. for stone where each face has the same texture
 * But this will not work for e.g. grass block which has different top, sides and bottom
 */
#define BLOCK_STANDARD_VERTEX(x,y) { \
             /* back - 0 */ \
             {{0.0f, 0.0f, 1.0f}, getTextureCoord(x, y, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE}, \
             {{1.0f, 0.0f, 1.0f}, getTextureCoord(x, y, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE}, \
             {{1.0f, 1.0f, 1.0f}, getTextureCoord(x, y, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE}, \
             {{0.0f, 1.0f, 1.0f}, getTextureCoord(x, y, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE}, \
             /* bottom - 4 */  \
             {{0.0f, 0.0f, 1.0f}, getTextureCoord(x, y, TextureCoordType::TOP_LEFT), BLOCK_SHADE_BOTTOM}, \
             {{1.0f, 0.0f, 1.0f}, getTextureCoord(x, y, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_BOTTOM}, \
             /* top - 6 */ \
             {{0.0f, 1.0f, 1.0f}, getTextureCoord(x, y, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_TOP}, \
             {{1.0f, 1.0f, 1.0f}, getTextureCoord(x, y, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_TOP}, \
             /* front - 8 */ \
             {{0.0f, 0.0f, 0.0f}, getTextureCoord(x, y, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE}, \
             {{1.0f, 0.0f, 0.0f}, getTextureCoord(x, y, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE}, \
             {{1.0f, 1.0f, 0.0f}, getTextureCoord(x, y, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE}, \
             {{0.0f, 1.0f, 0.0f}, getTextureCoord(x, y, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE} \
            }

/**
 * This should be used in combination with BLOCK_STANDARD_VERTEX.
 * It defines optimisations for face addition to prevent drawing
 * faces which are unnecessary
 */
#define BLOCK_STANDARD_INDICIES(FaceFlags, gameObject) \
        if((FaceFlags & BlockFace::BACK) == BlockFace::BACK){ \
            gameObject.indicies.insert(gameObject.indicies.end(), {0,1,3,1,2,3}); \
        } \
        if((FaceFlags & BlockFace::BOTTOM) == BlockFace::BOTTOM){ \
            gameObject.indicies.insert(gameObject.indicies.end(), {8,5,4,8,9,5}); \
        } \
        if((FaceFlags & BlockFace::TOP) == BlockFace::TOP){ \
            gameObject.indicies.insert(gameObject.indicies.end(), {10,11,7,11,6,7}); \
        } \
        if((FaceFlags & BlockFace::LEFT) == BlockFace::LEFT){ \
            gameObject.indicies.insert(gameObject.indicies.end(), {9,2,1,9,10,2}); \
        } \
        if((FaceFlags & BlockFace::RIGHT) == BlockFace::RIGHT){ \
            gameObject.indicies.insert(gameObject.indicies.end(), {0,3,8,3,11,8}); \
        } \
        if((FaceFlags & BlockFace::FRONT) == BlockFace::FRONT){ \
            gameObject.indicies.insert(gameObject.indicies.end(), {8,10,9,11,10,8}); \
        }
