#include <stdio.h>
#include <stdlib.h>

#include "block.h"

char* _get_model_name(Block *block, PlayerType player) 
{
	char *model_name = NULL;
    switch (block->type) {
        case PAWN_TYPE_PAWN: 
			model_name = "objs/tshape.obj";
			block->height = 0.05;
		break;
        case PAWN_TYPE_ROOK: 
			model_name = "objs/icapshape.obj";
			block->height = 0.05;
		break;
        case PAWN_TYPE_KNIGHT: 
			model_name = "objs/sqtshape.obj";
			block->height = 0.05;
		break;
        case PAWN_TYPE_BISHOP: 
			model_name = "objs/squareshape.obj";
			block->height = 0.05;
		break;
        case PAWN_TYPE_QUEEN: 
			model_name = "objs/nshape.obj";
			block->height = 0.05;
		break;
        case PAWN_TYPE_KING: 
			model_name = "objs/king.obj";
			block->height = 0.05;
		break;
    }
	return model_name;
}

Block* create_block(BlockType type, PlayerType player)
{
    Block *block = malloc(sizeof(Block));
	block->pos[0] = 0;
	block->pos[1] = 0;
	block->pos[2] = 0;
	block->width = 0.05f;

	/* block colors */
	if (player == PLAYER_TYPE_BLACK) {
		block->color[R] = 0.01f;
		block->color[G] = 0.01f;
		block->color[B] = 0.01f;
		block->color[A] = 1.0f;
	}
	else {
		block->color[R] = 0.09f;
		block->color[G] = 0.09f;
		block->color[B] = 0.09f;
		block->color[A] = 1.0f;
	}
	block->color_selected[R] = 0.05f;
	block->color_selected[G] = 0.05f;
	block->color_selected[B] = 0.08f;

	block->type = type;
	block->player = player;
	block->height = 0.1f + ((GLdouble)type/(GLdouble)PAWN_TYPE_COUNT);

    char *model_name = _get_model_name(block, player);

    /* load the model in case */
    if (model_name) {
        block->model = (GLMmodel*) malloc(sizeof(GLMmodel));
		block->model = glmReadOBJ(model_name);
    }
	return block;
}


void display_block(Block *block, BlockState state) {
     glPushMatrix();

    /* draw block*/
    glTranslated(block->pos[0], block->pos[1], block->pos[2]);
	glScalef(block->width, block->height, block->width);

    if (block->model) {
		/* material colour */
		if (state == PAWN_SELECTED) {
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, block->color_selected);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, block->color_selected);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, block->color_selected);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 2.5f);
		}
		else {
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, block->color);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, block->color);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, block->color);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.5f);
		}
        glmDraw(block->model, GLM_SMOOTH);
    }
    glPopMatrix();
}

void destroy_block(Block *block)
{
    free(block->model);
	free(block);
	block = NULL;
}
