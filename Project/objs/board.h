#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

// #include "pawn.h"

#ifndef CHESSBOARD_h
#define CHESSBOARD_h


#define NUM_CELLS 8
#define TOTAL_CELLS (NUM_CELLS*NUM_CELLS)
#define CELL(x,y,z) (x+(NUM_CELLS*(y))+(z*NUM_CELLS*NUM_CELLS))
#define CELLY(cell) ((int)((float)cell/(float)NUM_CELLS))
#define CELLX(cell) (cell - (NUM_CELLS * CELLY(cell)))
#define CELL_CURRENT -2
#define CELL_NONE -1
#define R 0
#define G 1
#define B 2
#define A 3

typedef struct {
	GLdouble pos[3]; /* placeable, x, y, z */

	GLdouble cell_width;
	GLdouble cell_height;

	GLfloat color_dark[4];
	GLfloat color_clear[4];
	GLfloat color_specular[4];

    int cell_highlighted;
    int cell_selected;
    GLfloat color_selected[4];

	PlayerType player_turn;

	Board **board;
} Tetris_board;

Tetris_board *create_tetris_board();
void destroy_tetris_board(Tetris_board *cboard);
void display_tetris_board(Tetris_board *cboard);

void highlight_cell(Tetris_board *cboard, int x, int y);
void highlight_cell_up(Tetris_board *cboard);
void highlight_cell_down(Tetris_board *cboard);
void highlight_cell_left(Tetris_board *cboard);
void highlight_cell_right(Tetris_board *cboard);
void select_cell(Tetris_board *cboard, int cell);

// void tetris_board_place_pawn(Tetris_board *cboard, Pawn *pawn, int cell);
// void tetris_board_clear_cell(Tetris_board *cboard, int cell);

#endif