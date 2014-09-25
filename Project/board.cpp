#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"

void destroy_tetris_board(Tetris_board *cboard)
{
    //free(cboard->board); cboard->board = NULL;
	free(cboard);        cboard = NULL;
}

Tetris_board * create_tetris_board()
{
    Tetris_board *cboard ;//= malloc(sizeof(Tetris_board));
	cboard->pos[0] = 0;
	cboard->pos[1] = 0;
	cboard->pos[2] = 0;

	cboard->cell_height = 1.0f / NUM_CELLS;
	cboard->cell_width  = 1.0f / NUM_CELLS;
	
	/* colors */
	cboard->color_dark[R] = 0.3f; cboard->color_dark[G] = 0.3f;
	cboard->color_dark[B] = 0.4f; cboard->color_dark[A] = 1.0f;

	cboard->color_clear[R] = 1.0f; cboard->color_clear[G] = 1.0f;
	cboard->color_clear[B] = 1.0f; cboard->color_clear[A] = 1.0f;

	cboard->color_selected[R] = 0.0f; cboard->color_selected[G] = 0.0f;
	cboard->color_selected[B] = 1.0f; cboard->color_selected[A] = 0.2f;
	
	cboard->color_specular[R] = 1.0f; cboard->color_specular[G] = 1.0f;
	cboard->color_specular[B] = 1.0f; cboard->color_specular[A] = 1.0f;

	//cboard->player_turn = WHITE;

    /* select no cell */
    cboard->cell_highlighted = CELL_NONE;
    cboard->cell_selected =  CELL_NONE;

	/* logical cells for the pawn */
	//cboard->board = malloc(sizeof(Pawn*) * NUM_CELLS * NUM_CELLS);
	//memset(cboard->board, 0, sizeof(Pawn*) * NUM_CELLS * NUM_CELLS);

	return cboard;
}

void highlight_cell(Tetris_board* c, int x, int y) {
    c->cell_highlighted = CELL(x,y,0);
}

void display_tetris_board(Tetris_board *cboard) {
    glPushMatrix();
    glTranslatef(cboard->pos[0], cboard->pos[1], cboard->pos[2]);
    GLdouble x, y;
    int color = 0;
    
	int xcell = -1;
	int ycell;
	int zcell=0;
	GLdouble step = cboard->cell_width;
    for (x=-0.5f; x<0.5f; x+=step){
		xcell++;
		ycell = NUM_CELLS;

    	color = 1 - color;
    	for (y=-0.5f; y<0.5f; y+=step){
			ycell--;

    		/* flip color */
    		color = 1 - color;
    
    		/* choose material color */
            if (cboard->cell_highlighted == CELL(xcell, ycell,zcell)) {
                glMaterialfv(GL_FRONT, GL_AMBIENT, cboard->color_selected);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, cboard->color_selected);
                glMaterialfv(GL_FRONT, GL_SPECULAR, cboard->color_specular);
                glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
            }
            else {
                if (color) { 
                    glMaterialfv(GL_FRONT, GL_AMBIENT, cboard->color_dark);
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, cboard->color_dark);
                    glMaterialfv(GL_FRONT, GL_SPECULAR, cboard->color_specular);
                    glMaterialf(GL_FRONT, GL_SHININESS, 60.0f);
                }
                else {
                    glMaterialfv(GL_FRONT, GL_AMBIENT, cboard->color_clear);
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, cboard->color_clear);
                    glMaterialfv(GL_FRONT, GL_SPECULAR, cboard->color_specular);
                    glMaterialf(GL_FRONT, GL_SHININESS, 40.0f);
                }
            }

    		/* draw cell */
    		glBegin(GL_QUADS);
				glNormal3f(0.0,0.0,1.0);
    			glVertex3d(x, 0, y);
    			glVertex3d(x+step, 0, y);
    			glVertex3d(x+step, 0, y+step);
    			glVertex3d(x, 0, y+step);
    		glEnd();

			
    	}
   }
   glPopMatrix();
}

void highlight_cell_up(Tetris_board *cboard)
{
	int celly = CELLY(cboard->cell_highlighted);
	celly += celly == NUM_CELLS-1 ? -NUM_CELLS+1 : 1; 
    cboard->cell_highlighted = CELL(CELLX(cboard->cell_highlighted), celly,0);
}
void highlight_cell_down(Tetris_board *cboard)
{
	int celly = CELLY(cboard->cell_highlighted);
	celly -= celly == 0 ? -NUM_CELLS + 1 : 1; 
    cboard->cell_highlighted = CELL(CELLX(cboard->cell_highlighted), celly,0);
}
void highlight_cell_left(Tetris_board *cboard)
{
	int cellx = CELLX(cboard->cell_highlighted);
	cellx += cellx == 0 ? NUM_CELLS-1 : -1; 
    cboard->cell_highlighted = CELL(cellx, CELLY(cboard->cell_highlighted),0);
}
void highlight_cell_right(Tetris_board *cboard)
{
	int cellx = CELLX(cboard->cell_highlighted);
	cellx += cellx == NUM_CELLS-1 ? -NUM_CELLS+1 : 1; 
    cboard->cell_highlighted = CELL(cellx, CELLY(cboard->cell_highlighted),0);
}

// void set_turn(Tetris_board *cboard, PlayerType player) {
// 	cboard->player_turn = player;
// }
// void flip_turn(Tetris_board *cboard) {
// 	cboard->player_turn = 
// 		cboard->player_turn == WHITE ? BLACK
// 												 : WHITE;
// }

void select_cell(Tetris_board *cboard, int cell)
{
	int cell_wish = cell == CELL_CURRENT ? cboard->cell_highlighted : cell;
	//Pawn *p = get_pawn(cboard, cell_wish);
	// if (p) {
	// 	if (p->player == cboard->player_turn) {
	// 		/* own pawn selected -- clear selection / select pawn */
	// 		cboard->cell_selected = cell_wish == cboard->cell_selected ? CELL_NONE : cell_wish;
	// 	}
	// 	else {
	// 		if(CELL_NONE != cboard->cell_selected) {
	// 			/* opponent pawn selected -- take */
	// 			tetris_board_clear_cell(cboard, cell_wish);
	// 			//Pawn *taker = get_pawn(cboard, cboard->cell_selected);
	// 			tetris_board_clear_cell(cboard, cboard->cell_selected);
	// 			//tetris_board_place_pawn(cboard, taker, cell_wish);;
	// 			cboard->cell_selected = CELL_NONE;
	// 			flip_turn(cboard);
	// 		}
	// 	}
	// }
	// else {
	// 	/* empty cell selected */
	// 	if(CELL_NONE != cboard->cell_selected) {
	// 		/* move */
	// 		//Pawn *mover = get_pawn(cboard, cboard->cell_selected);
	// 	    tetris_board_clear_cell(cboard, cboard->cell_selected);
	// 		//tetris_board_place_pawn(cboard, mover, cell_wish);;
	// 	    flip_turn(cboard);
	// 	}
	// 	cboard->cell_selected = CELL_NONE;
	// }
}

void tetris_board_clear_cell(Tetris_board *cboard, int cell)
{
	//cboard->board[cell] = NULL;
}
