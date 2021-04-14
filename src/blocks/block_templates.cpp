
/**
 * This defines optimised list of vertecies to be used in a block
 * This definition should be used either as argument for insert or list creation
 */
#define BLOCK_STANDARD_VERTEX(xtop,ytop,xside,yside,xbottom,ybottom) { \
             /* back - 0 */ \
             {{0.0f, 0.0f, 1.0f}, GetTextureCoord(xside, yside, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE}, \
             {{1.0f, 0.0f, 1.0f}, GetTextureCoord(xside, yside, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE}, \
             {{1.0f, 1.0f, 1.0f}, GetTextureCoord(xside, yside, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE}, \
             {{0.0f, 1.0f, 1.0f}, GetTextureCoord(xside, yside, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE}, \
             /* bottom - 4 */  \
             {{0.0f, 0.0f, 0.0f}, GetTextureCoord(xbottom, ybottom, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_BOTTOM}, \
             {{1.0f, 0.0f, 0.0f}, GetTextureCoord(xbottom, ybottom, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_BOTTOM}, \
             {{0.0f, 0.0f, 1.0f}, GetTextureCoord(xbottom, ybottom, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_BOTTOM}, \
             {{1.0f, 0.0f, 1.0f}, GetTextureCoord(xbottom, ybottom, TextureCoordType::TOP_LEFT), BLOCK_SHADE_BOTTOM}, \
             /* top - 8 */ \
             {{0.0f, 1.0f, 1.0f}, GetTextureCoord(xtop, ytop, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_TOP}, \
             {{1.0f, 1.0f, 1.0f}, GetTextureCoord(xtop, ytop, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_TOP}, \
             {{1.0f, 1.0f, 0.0f}, GetTextureCoord(xtop, ytop, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_TOP}, \
             {{0.0f, 1.0f, 0.0f}, GetTextureCoord(xtop, ytop, TextureCoordType::TOP_LEFT), BLOCK_SHADE_TOP}, \
             /* front - 12 */ \
             {{0.0f, 0.0f, 0.0f}, GetTextureCoord(xside, yside, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE}, \
             {{1.0f, 0.0f, 0.0f}, GetTextureCoord(xside, yside, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE}, \
             {{1.0f, 1.0f, 0.0f}, GetTextureCoord(xside, yside, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE}, \
             {{0.0f, 1.0f, 0.0f}, GetTextureCoord(xside, yside, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE} \
            }

/**
 * This should be used in combination with BLOCK_STANDARD_VERTEX.
 * It defines optimisations for face addition to prevent drawing
 * faces which are unnecessary
 * This definition should be used within function to fill in block optimisation checks
 */
#define INCLUDE_BLOCK_STANDARD_INDICIES(FaceFlags, gameObject) \
        if((FaceFlags & BlockFace::BACK) == BlockFace::BACK){ \
            gameObject.indicies.insert(gameObject.indicies.end(), {0,1,3,1,2,3}); \
        } \
        if((FaceFlags & BlockFace::BOTTOM) == BlockFace::BOTTOM){ \
            gameObject.indicies.insert(gameObject.indicies.end(), {4,7,6,4,5,7}); \
        } \
        if((FaceFlags & BlockFace::TOP) == BlockFace::TOP){ \
            gameObject.indicies.insert(gameObject.indicies.end(), {11,8,10,8,9,10}); \
        } \
        if((FaceFlags & BlockFace::LEFT) == BlockFace::LEFT){ \
            gameObject.indicies.insert(gameObject.indicies.end(), {13,2,1,13,14,2}); \
        } \
        if((FaceFlags & BlockFace::RIGHT) == BlockFace::RIGHT){ \
            gameObject.indicies.insert(gameObject.indicies.end(), {0,3,12,3,15,12}); \
        } \
        if((FaceFlags & BlockFace::FRONT) == BlockFace::FRONT){ \
            gameObject.indicies.insert(gameObject.indicies.end(), {12,14,13,15,14,12}); \
        }

/**
 * This defines optimised list of vertecies to be used in a flower
 * This definition should be used either as argument for insert or list creation
 */
#define BLOCK_FLOWER_VERTEX(x,y) { \
             /* back - 0 */ \
             {{0.0f, 0.0f, 1.0f}, GetTextureCoord(x, y, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE}, \
             {{1.0f, 0.0f, 1.0f}, GetTextureCoord(x, y, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE}, \
             {{1.0f, 1.0f, 1.0f}, GetTextureCoord(x, y, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE}, \
             {{0.0f, 1.0f, 1.0f}, GetTextureCoord(x, y, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE}, \
             /* front - 4 */ \
             {{0.0f, 0.0f, 0.0f}, GetTextureCoord(x, y, TextureCoordType::BOTTOM_LEFT), BLOCK_SHADE_SIDE}, \
             {{1.0f, 0.0f, 0.0f}, GetTextureCoord(x, y, TextureCoordType::BOTTOM_RIGHT), BLOCK_SHADE_SIDE}, \
             {{1.0f, 1.0f, 0.0f}, GetTextureCoord(x, y, TextureCoordType::TOP_RIGHT), BLOCK_SHADE_SIDE}, \
             {{0.0f, 1.0f, 0.0f}, GetTextureCoord(x, y, TextureCoordType::TOP_LEFT), BLOCK_SHADE_SIDE} \
            }

/**
 * This definition should be used in combination with BLOCK_FLOWER_VERTEX.
 * This definition contains list of indicies that should be used for flower.
 * This definition should be used either as argument for insert or list creation
 * The indicies must be listed both ways to make sure that the mesh is displayed
 * on both sides.
 */
#define BLOCK_FLOWER_INDICIES { \
            6,3,0,0,3,6, \
            6,5,0,0,5,6, \
            7,2,1,1,2,7, \
            1,4,7,7,4,1 \
        }
