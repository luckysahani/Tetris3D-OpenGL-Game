#ifndef BLOCK_h 
#define BLOCK_h

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "glm.h"

#define R 0
#define G 1
#define B 2
#define A 3

typedef enum block_state_t {
	PAWN_NORMAL,
	PAWN_SELECTED,
} BlockState;

typedef enum player_type_t {
	PLAYER_TYPE_WHITE,
	PLAYER_TYPE_BLACK,
	PLAYER_TYPE_COUNT,
} PlayerType;

typedef enum block_type_t {
	PAWN_TYPE_PAWN,
	PAWN_TYPE_KNIGHT,
	squareshape,
	PAWN_TYPE_ROOK,
	cube,
	ishape,
	PAWN_TYPE_COUNT,
} BlockType;

typedef struct {
	/* An object always starts with these fields */
	GLdouble pos[3];
	float z;
    GLMmodel *model;

	BlockType type;
	PlayerType player;
	GLdouble width;
	GLdouble height;

	GLfloat color[4];
	GLfloat color_specular[4];
	GLfloat color_selected[4];
} Block;

Block * create_block(BlockType type, PlayerType player);
void destroy_block(Block *block);
void display_block(Block *block, BlockState state);

#endif
