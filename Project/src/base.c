#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "base.h" 

void destroy_tetris_board(Tetris_board *cboard)
{
    free(cboard->board); cboard->board = NULL;
	free(cboard);        cboard = NULL;
}

Tetris_board * create_tetris_board()
{
    Tetris_board *cboard = malloc(sizeof(Tetris_board));
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

	cboard->player_turn = WHITE;

    /* select no cell */
    cboard->cell_highlighted = CELL_NONE;
    cboard->cell_selected =  CELL_NONE;

	/* logical cells for the block */
	cboard->board = malloc(sizeof(Block*) * NUM_CELLS * NUM_CELLS);
	memset(cboard->board, 0, sizeof(Block*) * NUM_CELLS * NUM_CELLS);

	return cboard;
}
void tetris_board_place_block_at_boardvalue(Tetris_board *cboard, Block *p, int cell ,int k)
{
	p->pos[0] = ((GLdouble)CELLX(cell)/NUM_CELLS) - 0.5f + cboard->cell_width/2;
	p->pos[1] = (float)((float)(k)/10);//((double) rand() / (RAND_MAX))/8;
	p->pos[2] = ((GLdouble)(NUM_CELLS-CELLY(cell)-1)/NUM_CELLS) - 0.5f + cboard->cell_height/2;
	//printf("Block placed at x=%f,y=%f and z=%f\n",p->pos[0],p->pos[2],p->pos[1] );

	cboard->board[cell] = p;
}
void tetris_board_place_block(Tetris_board *cboard, Block *p, int cell,int z ) {
	/* invert the position of the pieces along the y-axis */
	p->pos[0] = ((GLdouble)CELLX(cell)/NUM_CELLS) - 0.5f + cboard->cell_width/2;
	p->pos[1] = 0.5;//((double) rand() / (RAND_MAX))/8;
	p->pos[2] = ((GLdouble)(NUM_CELLS-CELLY(cell)-1)/NUM_CELLS) - 0.5f + cboard->cell_height/2;
	// printf("Block placed at x=%f,y=%f and z=%f\n",p->pos[0],p->pos[2],p->pos[1] );

	cboard->board[cell] = p;
}

void reduce_z_regularly(Tetris_board *cboard, Block *p, int cell)
{
	if(p->pos[1]>0.1)
	{
		p->pos[1] -= 0.1; 
	}
	else
	{
		// p->pos[1]=0;
	}
}
void set_z_to_zero(Tetris_board *cboard, Block *p, int cell,int k)
{
	float temp=k;
	temp=temp/10;
	printf("setting p->pos[1] to %d and temp =%f\n",k ,temp);
	p->pos[1]=temp;
	printf("Block placed at x=%f,y=%f and z=%f\n",p->pos[0],p->pos[2],p->pos[1] );
}
void reset_coordinates(Tetris_board *cboard, Block *p, int cell)
{
	p->pos[0] = ((GLdouble)CELLX(cell)/NUM_CELLS) - 0.5f + cboard->cell_width/2;
	// p->pos[1] = 0.5;//((double) rand() / (RAND_MAX))/8;
	p->pos[2] = ((GLdouble)(NUM_CELLS-CELLY(cell)-1)/NUM_CELLS) - 0.5f + cboard->cell_height/2;
	// cboard->board[cell] = p;
	printf("Resetting position p->pos[0] to %f and p->pos[2] to %f \n",p->pos[0],p->pos[2]);
	// p->pos[1]=temp;
	// printf("Block placed at x=%f,y=%f and z=%f\n",p->pos[0],p->pos[2],p->pos[1] );
}



// void highlight_cell(Tetris_board* c, int x, int y) {
//     c->cell_highlighted = CELL(x,y,0);
// }

Block *get_block(Tetris_board* c, int cell) {
	// printf("Asking for block\n");
	if(c->board[cell])
	{
		printf("Block exists at cell %d\n",cell );
	}
	else
	{
		// printf("Block does not exists at cell %d\n",cell );
	}
	return c->board[cell];
}

void display_tetris_board(Tetris_board *cboard,int board_status[8][8],int created_status[8][8]) {
    glPushMatrix();
    glTranslatef(cboard->pos[0], cboard->pos[1], cboard->pos[2]);
    GLdouble x, y;
    int color = 0;
    
	int xcell = -1;
	int ycell;
	int zcell=0;
	int i;
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

			/* draw block at cell */


//			ERROR PART
    		// printf("entering inside at i=%d and cell =%d\n",i,CELL(xcell, ycell,i));

    		if(board_status[xcell][ycell]>=0)
    		{
    			i=0;
    			if (cboard->board[CELL(xcell, ycell,i)]) {
					Block *block = cboard->board[CELL(xcell, ycell,i)];
					// printf("Entered ohh really at cell =%d\n",CELL(xcell, ycell,i));
					display_block(block, CELL(xcell, ycell,i)	);
				}
    		}
    		if((board_status[xcell][ycell]>=1)&&(created_status[xcell][ycell]==1))
    		{
    			i=1;
    			if (cboard->board[CELL(xcell, ycell,i)]) {
					Block *block = cboard->board[CELL(xcell, ycell,i)];
					// printf("Entered ohh really at cell =%d\n",CELL(xcell, ycell,i));
					display_block(block, CELL(xcell, ycell,i)	);
				}
    		}
    		if((board_status[xcell][ycell]>=2)&&(created_status[xcell][ycell]==1))
    		{
    			i=2;
    			if (cboard->board[CELL(xcell, ycell,i)]) {
					Block *block = cboard->board[CELL(xcell, ycell,i)];
					// printf("Entered ohh really at cell =%d\n",CELL(xcell, ycell,i));
					display_block(block, CELL(xcell, ycell,i)	);
				}
    		}
    		if((board_status[xcell][ycell]>=3)&&(created_status[xcell][ycell]==1))
    		{
    			i=3;
    			if (cboard->board[CELL(xcell, ycell,i)]) {
					Block *block = cboard->board[CELL(xcell, ycell,i)];
					// printf("Entered ohh really at cell =%d\n",CELL(xcell, ycell,i));
					display_block(block, CELL(xcell, ycell,i)	);
				}
    		}
    		if((board_status[xcell][ycell]>=4)&&(created_status[xcell][ycell]==1))
    		{
    			i=4;
    			if (cboard->board[CELL(xcell, ycell,i)]) {
					Block *block = cboard->board[CELL(xcell, ycell,i)];
					// printf("Entered ohh really at cell =%d\n",CELL(xcell, ycell,i));
					display_block(block, CELL(xcell, ycell,i)	);
				}
    		}
    		if((board_status[xcell][ycell]>=5)&&(created_status[xcell][ycell]==1))
    		{
    			i=5;
    			if (cboard->board[CELL(xcell, ycell,i)]) {
					Block *block = cboard->board[CELL(xcell, ycell,i)];
					// printf("Entered ohh really at cell =%d\n",CELL(xcell, ycell,i));
					display_block(block, CELL(xcell, ycell,i)	);
				}
    		}
    		if((board_status[xcell][ycell]>=6)&&(created_status[xcell][ycell]==1))
    		{
    			i=6;
    			if (cboard->board[CELL(xcell, ycell,i)]) {
					Block *block = cboard->board[CELL(xcell, ycell,i)];
					// printf("Entered ohh really at cell =%d\n",CELL(xcell, ycell,i));
					display_block(block, CELL(xcell, ycell,i)	);
				}
    		}

			// printf("just entered\n");
			// else
			// {
				for ( i = 0; i < board_status[xcell][ycell]; i++)
				{
					/* code */
					// printf("entering inside at i=%d and cell =%d\n",i,CELL(xcell, ycell,i));
				
					// Block *block = cboard->block[CELL(xcell, ycell,i)];//get_block(cboard, CELL(xcell, ycell,i));
					if (cboard->board[CELL(xcell, ycell,i)]) {
						Block *block = cboard->board[CELL(xcell, ycell,i)];
						// printf("Entered ohh really at cell =%d\n",CELL(xcell, ycell,i));
						display_block(block, CELL(xcell, ycell,i)	);
					}
				}
			// }


//			ERROR PART OVER
    	}
   }




 //   xcell = -1;;
 //   for (x=-0.5f; x<0.5f; x+=step){
	// 	xcell++;
	// 	ycell = NUM_CELLS;

 //    	// color = 1 - color;
 //    	for (y=-0.5f; y<0.5f; y+=step){
	// 		ycell--;
	// 		for ( i = 0; i < 1; i++)
	// 		{
	// 			/* code */
	// 			// printf("entering inside at i=%d and cell =%d\n",i,CELL(xcell, ycell,i));
			
	// 			// Block *block = cboard->block[CELL(xcell, ycell,i)];//get_block(cboard, CELL(xcell, ycell,i));
	// 			if (cboard->board[CELL(xcell, ycell,i)]) {
	// 				Block *block = cboard->board[CELL(xcell, ycell,i)];
	// 				// printf("Entered ohh really at cell =%d\n",CELL(xcell, ycell,i));
	// 				display_block(block, CELL(xcell, ycell,i)	);
	// 			}
	// 		}
	// 	}
	// }
   // printf("Displaying board\n");
   glPopMatrix();
}


// void highlight_cell_up(Tetris_board *cboard)
// {
// 	int celly = CELLY(cboard->cell_highlighted);
// 	celly += celly == NUM_CELLS-1 ? -NUM_CELLS+1 : 1; 
//     cboard->cell_highlighted = CELL(CELLX(cboard->cell_highlighted), celly,0);
// }
// void highlight_cell_down(Tetris_board *cboard)
// {
// 	int celly = CELLY(cboard->cell_highlighted);
// 	celly -= celly == 0 ? -NUM_CELLS + 1 : 1; 
//     cboard->cell_highlighted = CELL(CELLX(cboard->cell_highlighted), celly,0);
// }
// void highlight_cell_left(Tetris_board *cboard)
// {
// 	int cellx = CELLX(cboard->cell_highlighted);
// 	cellx += cellx == 0 ? NUM_CELLS-1 : -1; 
//     cboard->cell_highlighted = CELL(cellx, CELLY(cboard->cell_highlighted),0);
// }
// void highlight_cell_right(Tetris_board *cboard)
// {
// 	int cellx = CELLX(cboard->cell_highlighted);
// 	cellx += cellx == NUM_CELLS-1 ? -NUM_CELLS+1 : 1; 
//     cboard->cell_highlighted = CELL(cellx, CELLY(cboard->cell_highlighted),0);
// }

void set_turn(Tetris_board *cboard, PlayerType player) {
	cboard->player_turn = player;
	printf("Player turn changed\n");
}
void flip_turn(Tetris_board *cboard) {
	// cboard->player_turn = 
		// cboard->player_turn == WHITE ? BLACK: WHITE;
		printf("Flipped\n");
}

void select_cell(Tetris_board *cboard, int cell)
{
	printf("Selectcell called\n");
	int cell_wish = cell == CELL_CURRENT ? cboard->cell_highlighted : cell;
	Block *p = get_block(cboard, cell_wish);
	if (p) {
		if (p->player == cboard->player_turn) {
			/* own block selected -- clear selection / select block */
			cboard->cell_selected = cell_wish == cboard->cell_selected ? CELL_NONE : cell_wish;
		}
		else {
			if(CELL_NONE != cboard->cell_selected) {
				/* opponent block selected -- take */
				tetris_board_clear_cell(cboard, cell_wish);
				Block *taker = get_block(cboard, cboard->cell_selected);
				tetris_board_clear_cell(cboard, cboard->cell_selected);
				tetris_board_place_block(cboard, taker, cell_wish,0);;
				cboard->cell_selected = CELL_NONE;
				//flip_turn(cboard);
			}
		}
	}
	else {
		/* empty cell selected */
		if(CELL_NONE != cboard->cell_selected) {
			/* move */
			Block *mover = get_block(cboard, cboard->cell_selected);
		    tetris_board_clear_cell(cboard, cboard->cell_selected);
			tetris_board_place_block(cboard, mover, cell_wish,0);
		    flip_turn(cboard);
		}
		cboard->cell_selected = CELL_NONE;
	}
}

void tetris_board_clear_cell(Tetris_board *cboard, int cell)
{
	// cboard->board[cell] = NULL;
	printf("Clearing\n");
}
