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
#include "viewer.h"
#include "glm.h"

#include <AL/alut.h>

#include <stdio.h>
#include <stdlib.h> 
#define HEIGHT 800
#define WIDTH 800

Tetris_board *tetris_board;
Block *block[8][8][6]; 

// GLfloat ambientLight[4] = { 0.4f, 0.4f, 0.5f, 1.0f };
// +GLfloat diffuseLight[4] = { 0.6f, 0.6f, 0.5f, 1.0f };
// +GLfloat specularLight[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
// +GLfloat position[4] = { 1.0f, 1.0f, 1.0f, 0.3f };
/* some lighting */
GLfloat ambientLightA[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuseLightA[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat ambientLightB[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat diffuseLightB[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

GLfloat specularLightA[4] = { 0.3f, 0.3f, 0.3f, 0.4f };
GLfloat specularLightB[4] = { 0.0f, 0.0f, 0.0f, 0.4f };

GLfloat lightPositionA[4] = { -100.0f, 100.0f, -100.0f, 1.0f };
GLfloat lightPositionB[4] = {  100.0f, 100.0f,  100.0f, 1.0f };

// GLfloat diffuseLightA[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

/* the viewer */
Viewer *viewer;

int time_status=0;
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
int created_status[8][8];
Block *current_block;
int x_prev,y_prev;



ALuint buffer, source; 
void loadSound(){
  buffer = alutCreateBufferFromFile("3.wav");
  alGenSources(1, &source);
  alSourcei(source, AL_BUFFER, buffer);
}
void cleanUpSound(){
  alDeleteSources(1, &source);
  alDeleteBuffers(1, &buffer);
}
void playSound(){
  alSourcePlay(source);
}
void init() {

	tetris_board = create_tetris_board();
	viewer = create_viewer((Placeable *)tetris_board);
	int i,j,k;
	// itn k=0.0;
	for ( i = 0; i < 8; ++i)
	{
		for ( j = 0; j < 8; ++j)
		{
			board_status[i][j]=0;
			for ( k = 0; k < 6; k++)
			{
				block[i][j][k] = create_block(ishape, 1);
			}
		}
	}
	// int x,y;
	// for (player = 0; player < PLAYER_TYPE_COUNT; player++) {
	// 	// for (i=0;  i<8;  i++) pawn[player][i] = create_pawn(PAWN_TYPE_PAWN, player);
	// 	// for (i=8;  i<10; i++) pawn[player][i] = create_pawn(PAWN_TYPE_ROOK, player);
	// 	// for (i=10; i<12; i++) pawn[player][i] = create_pawn(PAWN_TYPE_KNIGHT, player);
	// 	// for (i=12; i<14; i++) pawn[player][i] = create_pawn(PAWN_TYPE_BISHOP, player);
	// 	block[player][14] = create_pawn(PAWN_TYPE_QUEEN, player);
	// 	// pawn[player][15] = create_pawn(PAWN_TYPE_KING, player);
	// }
	
	glClearColor (0.8, 0.8, 1.0, 1.0);
	// glClearColor (0.0f,0.2f,0.2f, 1.0);
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

// void play()
// {
//     ALuint helloBuffer, helloSource;
// 	// alGetError();
// 	helloBuffer = alutCreateBufferFromFile ("3.wav");
// 	alGenSources (1, &helloSource);
// 	alSourcei (helloSource, AL_BUFFER, helloBuffer);
// 	alSourcePlay (helloSource);
// 	// alutSleep (1);
// 	printf("hellobuffer\n");
// 	// alutExit (); 
// }

void display() {
	static int shouldPlaySound = 1;
	if(shouldPlaySound){
	loadSound();
	playSound();
	shouldPlaySound = 0;
	}
	
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

   display_tetris_board(tetris_board,board_status,created_status);

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
	while(y_temp==0 && x_temp==0)
	{
		y_temp=rand()%8;
		x_temp=rand()%8;
	}
	int current_z=board_status[x_temp][y_temp];
	// Block *square=current_block;
	printf("SquareShape created at x_temp==%d,y_temp==%d,color=%d,cell value =%d and board_staus=%d\n",x_temp,y_temp,color_block, CELL(x_temp, y_temp,current_z),current_z );
	current_block=set_block(squareshape, color_block,block[x_temp][y_temp][current_z]);
	// current_block=block[x_temp][y_temp][current_z];
	glmScale(current_block->model,0.6);
	tetris_board_place_block(tetris_board, current_block, CELL(x_temp, y_temp,current_z),current_z);
}





//This creates an Ishape Object
void create_ishape_block()
{
	while(y_temp>5)
	{
		y_temp=rand()%8;
	}
	int current_z=board_status[x_temp][y_temp];
	printf("Ishape created at x_temp==%d,y_temp==%d,color=%d,cell value =%d and board_staus=%d\n",x_temp,y_temp,color_block, CELL(x_temp, y_temp,current_z),current_z );
	current_block= set_block(ishape, color_block,block[x_temp][y_temp][current_z]);
	// current_block=block[x_temp][y_temp][current_z];
	tetris_board_place_block(tetris_board, current_block, CELL(x_temp, y_temp,current_z),current_z);
}





//This creates an Cube Object
void create_cube_block()
{
	while(y_temp>6)
	{
		y_temp=rand()%8;
	}
	while(x_temp>6)
	{
		x_temp=rand()%8;
	}
	while(y_temp==0 && x_temp==0)
	{
		y_temp=rand()%8;
		x_temp=rand()%8;
	}
	int current_z=board_status[x_temp][y_temp];
	printf("Cube created at x_temp==%d,y_temp==%d,color=%d,cell value =%d and board_staus=%d\n",x_temp,y_temp,color_block, CELL(x_temp, y_temp,current_z),current_z );
	current_block=set_block(cube, color_block,block[x_temp][y_temp][current_z]);
	// current_block=block[x_temp][y_temp][current_z];
	glmScale(current_block->model,0.6);
	tetris_board_place_block(tetris_board,current_block, CELL(x_temp, y_temp,current_z),current_z);
}




//To move the block by 0.1 units downward
void move_block_down_by_one_step()
{
	int current_z=board_status[x_temp][y_temp];
	if(current_z==6){
		printf("Game over\n");
		exit(0);
	}
	printf("moved down 1 step\n");
	reduce_z_regularly(tetris_board, current_block, CELL(x_temp,y_temp,current_z));

}






//Update board status by 1 i.e now the blocks should come above the already placed block
void increment_board_status()
{
	// tetris_board_place_block_at_boardvalue(tetris_board, current_block, CELL(x_temp, y_temp,current_z),temp);
	printf("Updating board statu\n");
	int i,j;
	// if(k==1){
	// 	board_status[x_temp][y_temp]++;
	// } 
	// // else if(k==2){
	// // 	board_status[x_temp][y_temp]++;
	// // 	board_status[x_temp][y_temp+1]++;
	// // 	// board_status[x_temp][y_temp+2]++;
	// // }
	// else if(k==3){
	// 	for ( i = 0; i < 2; ++i)
	// 	{
	// 		for ( j = 0; j < 2; ++j)
	// 		{
	// 			board_status[x_temp+i][y_temp+j]++;
	// 			printf("Updating board status for (%d,%d)\n",x_temp+i,y_temp+j );
	// 			// board_status[x_temp][y_temp]++;break;
	// 		}
	// 	}
	// }
	board_status[x_temp][y_temp]++;
	int current_z=board_status[x_temp][y_temp];
	printf("board_status with x_temp=%d,y_temp=%d ,ccell value==%d and board_status=%d\n\n",x_temp,y_temp, CELL(x_temp, y_temp,current_z),current_z);

}




//Place the block at the bottom most possible and then increment the board status
void place_block()
{
	int current_z=board_status[x_temp][y_temp];
	set_z_to_zero(tetris_board, current_block, CELL(x_temp,y_temp,current_z),(current_z));
	increment_board_status();
	created_status[x_temp][y_temp]=0;
}





//The main code is implemented here
void update_game()
{
	int current_z=board_status[x_temp][y_temp];
	if(current_z==6){
			printf("Game over\n");
			exit(0);
		}
	if(flag==1)
	{
		// x_prev=x_temp;
		// y_prev=x_temp;
		printf("\n\n");
		flag=0;
		count=height/0.1;
		k=rand()%3+ 1;//k=3;
		x_temp=rand()%8 ;						//x value of block
		y_temp=rand()%8 ;						//y value of block
		// x_temp=3;y_temp=5;
		// k=3;
		// x_temp=0;y_temp=0;
		color_block=rand()%3;					//color of block
		if(k==1){create_squareshape_block();}	//Creates an square shape object
		if(k==2){create_ishape_block();}		//creates an ishape object
		if(k==3){create_cube_block();}			//created an cube object
		// board_status[x_prev][y_prev]++;
		printf("Created the blocks\n");
		created_status[x_temp][y_temp]=1;
	}
	else
	{
		count--;								//this keeps the track of the new block movement i.e its each decrement means decrement of z by 0.1
	}
	move_block_down_by_one_step();				//decrement z by 0.1
	if(count==current_z)		// if the block is just above another already placed block
	{
		place_block();							//place this new block
		if(current_z==5){		//if the height of game>5 exit the game baby
			printf("Game over\n");
			exit(0);
		}
		flag=1;									
	}
}






void timer(int extra) {
	glutPostRedisplay();
	if(time_status==50){update_game();time_status=0;}
	time_status++;
	glutTimerFunc(1, timer, 0);
	// glutTimerFunc(200, update_game,0);	
}

void keypressed(unsigned char key, int x, int y) {

	if (key == 's') { viewer->pos[2]+=0.05;}
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
	// ALuint helloBuffer, helloSource;
	// alutInit(0, NULL);
	// alGetError();
	// helloBuffer = alutCreateBufferFromFile ("wav/2.wav");
	// alGenSources (1, &helloSource);
	// alSourcei (helloSource, AL_BUFFER, helloBuffer);
	// alSourcePlay (helloSource);
	// alutExit ();

	glutInit(&argc, argv);
	alutInit(0, NULL);
	alGetError();
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize (1200, 800);
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


