#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <string.h>
#include <stdlib.h>

#include "base.h"
#include "block.h"
#include "placer.h"
#include "table.h"
#include "viewer.h"
#include "glm.h"
#include <stdlib.h> 
#define HEIGHT 800
#define WIDTH 800

Tetris_board *tetris_board;
Block *block[8][8][6]; 
Table *table;

/* some lighting */
GLfloat ambientLightA[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuseLightA[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat ambientLightB[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat diffuseLightB[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

GLfloat specularLightA[4] = { 0.3f, 0.3f, 0.3f, 0.4f };
GLfloat specularLightB[4] = { 0.0f, 0.0f, 0.0f, 0.4f };

GLfloat lightPositionA[4] = { -100.0f, 100.0f, -100.0f, 1.0f };
GLfloat lightPositionB[4] = {  100.0f, 100.0f,  100.0f, 1.0f };

/* the viewer */
Viewer *viewer;


int isClicked_right,isClicked_left;
int k=0;
float height=0.5;
float count=0;				
int x_temp;
int flag=1;
int y_temp,temp=0;
int count_squareshape=0,count_ishape=0,count_cube=0,count_block=0;
int color_block;
int board_status[8][8];

void init() {
    /* the tetris_board and the table and the player (viewer)*/
	tetris_board = create_tetris_board();
	table      = create_table();
	place_on_model(tetris_board->pos, (Placeable *) table);
	viewer = create_viewer((Placeable *)tetris_board);
	int i,j;
	for ( i = 0; i < 8; ++i)
	{
		for ( j = 0; j < 8; ++j)
		{
			board_status[i][j]=0;
		}
	}

	glClearColor (0.0f,0.2f,0.2f, 1.0);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
}

void end() {
	destroy_tetris_board(tetris_board);
	destroy_viewer(viewer);
}

void display() {
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen and depth buffers
   glLoadIdentity();
	
   /* lighting */
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLightA);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightA);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specularLightA);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPositionA);

   glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLightB);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightB);
   glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightB);
   glLightfv(GL_LIGHT1, GL_POSITION, lightPositionB);
   
   observe_from_viewer(viewer);

   //display_table(table);
   display_tetris_board(tetris_board);

   glFlush();
   glutSwapBuffers();
}

void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}










//This creates an Square shape Object
void create_squareshape_block()
{
	count_squareshape++;
	// printf("CELL(x_temp, y_temp,board_status[x_temp][y_temp])==%d\n",CELL(x_temp, y_temp,board_status[x_temp][y_temp]));
	printf("SquareShape created at x_temp==%d,y1==%d and board_staus=%d\n",x_temp,y_temp,board_status[x_temp][y_temp] );
	block[x_temp][y_temp][board_status[x_temp][y_temp]] = create_block(squareshape, color_block);
	glmScale(block[x_temp][y_temp][board_status[x_temp][y_temp]]->model,0.6);
	tetris_board_place_block(tetris_board, block[x_temp][y_temp][board_status[x_temp][y_temp]], CELL(x_temp, y_temp,board_status[x_temp][y_temp]),board_status[x_temp][y_temp]);
}
//This creates an Ishape Object
void create_ishape_block()
{

	while(y_temp>5)
	{
		y_temp=rand()%8+1;
	}
	printf("Ishape created at x_temp==%d,y_temp==%d and board_staus=%d\n",x_temp,y_temp,board_status[x_temp][y_temp] );
	count_ishape++;
	block[x_temp][y_temp][board_status[x_temp][y_temp]] = create_block(ishape, color_block);
	tetris_board_place_block(tetris_board, block[x_temp][y_temp][board_status[x_temp][y_temp]], CELL(x_temp, y_temp,board_status[x_temp][y_temp]),board_status[x_temp][y_temp]);
}
//This creates an Cube Object
void create_cube_block()
{
	while(y_temp>6)
	{
		y_temp=rand()%8+1;
	}
	while(x_temp>6)
	{
		x_temp=rand()%8+1;
	}
	printf("Cube created at x_temp==%d,y1==%d and board_staus=%d\n",x_temp,y_temp,board_status[x_temp][y_temp] );
	count_cube++;
	block[x_temp][y_temp][board_status[x_temp][y_temp]] = create_block(cube, color_block);
	glmScale(block[x_temp][y_temp][board_status[x_temp][y_temp]]->model,0.6);
	tetris_board_place_block(tetris_board, block[x_temp][y_temp][board_status[x_temp][y_temp]], CELL(x_temp, y_temp,board_status[x_temp][y_temp]),board_status[x_temp][y_temp]);
}
//To move the block by 0.1 units downward
void move_block_down_by_one_step()
{
	printf("moved down 1 step\n");
	reduce_z_regularly(tetris_board, block[x_temp][y_temp][board_status[x_temp][y_temp]], CELL(x_temp,y_temp,board_status[x_temp][y_temp]));

}
//Update board status by 1 i.e now the blocks should come above the already placed block
void increment_board_status()
{
	// tetris_board_place_block_at_boardvalue(tetris_board, block[x_temp][y_temp][board_status[x_temp][y_temp]], CELL(x_temp, y_temp,board_status[x_temp][y_temp]),temp);
	// board_status[x_temp][y_temp]++;
	printf("board_status with x_temp=%d,y_temp=%d and board_status=%d\n\n",x_temp,y_temp,board_status[x_temp][y_temp]);
	
}
//Place the block at the bottom most possible and then increment the board status
void place_block()
{
	set_z_to_zero(tetris_board, block[x_temp][y_temp][board_status[x_temp][y_temp]], CELL(x_temp,y_temp,board_status[x_temp][y_temp]),(board_status[x_temp][y_temp]));
	// tetris_board_place_block(tetris_board, block[x_temp][y_temp][board_status[x_temp][y_temp]], CELL(x_temp, y_temp,board_status[x_temp][y_temp]),2);
	increment_board_status();
}
//The main code is implemented here
void update_game()
{
	// printf("count==%f\n",count);
	if(board_status[x_temp][y_temp]>5){
			printf("Game over\n");
			exit(0);
		}
	if(flag==1)
	{
		printf("\n\n");
		flag=0;
		count=height/0.1;
		k=rand()%3+ 1;//k=3;
		x_temp=rand()%8 ;						//x value of block
		y_temp=rand()%8 ;						//y value of block
		// x_temp=3;y_temp=5;
		color_block=rand()%3;					//color of block
		if(k==1){create_squareshape_block();}	//Creates an square shape object
		if(k==2){create_ishape_block();}		//creates an ishape object
		if(k==3){create_cube_block();}			//created an cube object
		printf("Created the blocks\n");
	}
	else
	{
		count--;								//this keeps the track of the new block movement i.e its each decrement means decrement of z by 0.1
	}
	move_block_down_by_one_step();				//decrement z by 0.1
	if(count==board_status[x_temp][y_temp])		// if the block is just above another already placed block
	{
		place_block();							//place this new block
		if(board_status[x_temp][y_temp]>5){		//if the height of game>5 exit the game baby
			printf("Game over\n");
			exit(0);
		}
		flag=1;									
	}
}










void timer(int extra) {
	glutPostRedisplay();
	glutTimerFunc(200, timer, 0);
	glutTimerFunc(200, update_game,0);	
}

void keypressed(unsigned char key, int x, int y) {
	if (key == 's') { viewer->pos[2]+=0.05; }
	if (key == 'w') { viewer->pos[2]-=0.05; }
	if (key == 'a') { viewer->pos[0]-=0.05; }
	if (key == 'd') { viewer->pos[0]+=0.05; }
	if (key == 'm') { viewer->pos[1]+=0.05; }
	if (key == 'n') { viewer->pos[1]-=0.05; }
	// if (key == 'f') { highlight_cell_left(tetris_board); }
	// if (key == 'g') { highlight_cell_down(tetris_board); }
	// if (key == 'h') { highlight_cell_right(tetris_board); }
	// if (key == 't') { highlight_cell_up(tetris_board); }
	if (key == 'p') { select_cell(tetris_board, CELL_CURRENT); }
    if (key == 'x') { exit(0); }
}
void mouseMove(int x, int y) 
{ 	
	if (isClicked_left) { 
		viewer->pos[2]-=0.05;
	}
	else if (isClicked_right)
	{
		viewer->pos[2]+=0.05;
	}
}
void mouseButton(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON) 
	{
		if (state == GLUT_DOWN) { 
			viewer->pos[2]-=0.05;
			isClicked_left=1;
		}
		else  { 
			isClicked_left = 0; 
		}
		
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			viewer->pos[2]+=0.05;
			isClicked_right=1;
		}
		else
		{
			isClicked_right=0;
		}

	}
	if ((button == 3) ) 
   {
       if (state == GLUT_UP) return; 
       viewer->pos[0]-=0.05;
   }
   else if(button == 4)
   {
   		viewer->pos[0]+=0.05;
   }
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize (800, 800);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("3D-Tetris");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    glutKeyboardFunc(keypressed);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
	glutTimerFunc(0,timer,0);
	
    init();
	glutMainLoop();

	end();

	return 0;
}


