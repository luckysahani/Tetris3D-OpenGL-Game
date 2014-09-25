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

#define HEIGHT 800
#define WIDTH 800

Chessboard *chessboard;
Block *block[2][16];
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
int y_temp;
int count_squareshape=0,count_ishape=0,count_cube=0;
int color_block;

void init() {
    /* the chessboard and the table and the player (viewer)*/
	chessboard = create_chessboard();
	table      = create_table();

	/* place the chessboard on the table */
	place_on_model(chessboard->pos, (Placeable *) table);

	viewer = create_viewer((Placeable *)chessboard);

	/* the chess set */
	int player, i,i1;
	// for (player = 0; player < PLAYER_TYPE_COUNT; player++) {
		// for (i=0;  i<8;  i++) block[player][i] = create_block(PAWN_TYPE_PAWN, player);
		// for (i=8;  i<10; i++) block[player][i] = create_block(PAWN_TYPE_ROOK, player);
		// for (i=10; i<12; i++) block[player][i] = create_block(PAWN_TYPE_KNIGHT, player);
		// for (i=12; i<14; i++) block[player][i] = create_block(squareshape, player);
		// block[player][i] = create_block(squareshape, player);
		// block[player][i] = create_block(ishape, player);
	// }
	// for (i1 = 0; i1 < 300; ++i1)
	// {
	// 	glmScale(block[WHITE][i1]->model,0.6);
	// 	glmScale(block[BLACK][i1]->model,0.6);
	// }
	//glmScale(block[WHITE][12],0.5);
	
	/* place all the pieces */
	int x, y;
	/* -- white -- */
	// chessboard_place_block(chessboard, block[WHITE][8],  CELL(0, rand()/RAND_MAX*8));  /*rooks */
	// chessboard_place_block(chessboard, block[WHITE][9],  CELL(7, rand()/RAND_MAX*8));
	// chessboard_place_block(chessboard, block[WHITE][10], CELL(1, rand()/RAND_MAX*8));  knight 
	// chessboard_place_block(chessboard, block[WHITE][11], CELL(6, rand()/RAND_MAX*8));
	//chessboard_place_block(chessboard, block[WHITE][12], CELL(2, 3)); /* bishop */
	//chessboard_place_block(chessboard, block[WHITE][13], CELL(5, 6));
	// chessboard_place_block(chessboard, block[WHITE][14], CELL(3, rand()/RAND_MAX*8)); /* queen */
	//chessboard_place_block(chessboard, block[WHITE][15],CELL(3,1)); /* king */
//	for (x=0; x<5; x++){chessboard_place_block(chessboard, block[WHITE][x], CELL(x, rand()/RAND_MAX*8));}
	
	/* -- black -- */
	// rand()/RAND_MAX*8=7; chessboard_place_block(chessboard, block[BLACK][8],  CELL(0, rand()/RAND_MAX*8)); /* rooks */
	//      chessboard_place_block(chessboard, block[BLACK][9],  CELL(7, rand()/RAND_MAX*8));
	//      chessboard_place_block(chessboard, block[BLACK][10], CELL(1, rand()/RAND_MAX*8)); /* knight */
	//      chessboard_place_block(chessboard, block[BLACK][11], CELL(6, rand()/RAND_MAX*8));
	//      chessboard_place_block(chessboard, block[BLACK][12], CELL(2, rand()/RAND_MAX*8)); /* bishop */
	//      chessboard_place_block(chessboard, block[BLACK][13], CELL(5, rand()/RAND_MAX*8));
	//      chessboard_place_block(chessboard, block[BLACK][14], CELL(3, rand()/RAND_MAX*8)); /* queen */
	//      chessboard_place_block(chessboard, block[BLACK][15], CELL(4, rand()/RAND_MAX*8)); /* king */
	//		for (x=0; x<2; x++) chessboard_place_block(chessboard, block[BLACK][x], CELL(x, rand()/RAND_MAX*8));
	
    /* opengl initialisations */
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
	destroy_chessboard(chessboard);
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
   display_chessboard(chessboard);

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
void create_now(int k)
{
	x_temp=rand()%8 ;
	y_temp=rand()%8 ;
	color_block=rand()%3;
	//block[player][15] = create_block(ishape, player);
	switch(k)
	{
		case 1:
			// printf("x_temp==%d,y1==%d\n",x_temp,y_temp );
			count_squareshape++;
			printf("entered\n");
			block[WHITE][count_squareshape] = create_block(squareshape, color_block);
			glmScale(block[WHITE][count_squareshape]->model,0.6);
			chessboard_place_block(chessboard, block[WHITE][count_squareshape], CELL(x_temp, y_temp));
			break;
		case 2:
			while(y_temp>5)
			{
				y_temp=rand()%8+1;
			}
			printf("x_temp==%d,y1==%d\n",x_temp,y_temp );
			count_ishape++;
			block[WHITE][count_ishape] = create_block(ishape, color_block);
			chessboard_place_block(chessboard, block[WHITE][count_ishape], CELL(x_temp, y_temp));
			break;
		case 3:
			while(y_temp>6)
			{
				y_temp=rand()%8+1;
			}
			while(x_temp>6)
			{
				x_temp=rand()%8+1;
			}
			printf("x_temp==%d,y1==%d\n",x_temp,y_temp );
			count_cube++;
			block[1][count_cube] = create_block(cube, color_block);
			glmScale(block[1][count_cube]->model,0.6);
			chessboard_place_block(chessboard, block[1][count_cube], CELL(x_temp, y_temp));
			break;
		/*case 4:
			chessboard_place_block(chessboard, block[WHITE][11], CELL(x_temp, y_temp));*/
	}

}
void update_game()
{
	printf("count==%f\n",count);
	if(count==0)
	{
		count=height/0.1;
		k=rand()%3+ 1;
		// k=3;
		create_now(k);
	}
	else
	{
		count--;
	}


	switch(k){
	case 1:
		reduce_z_regularly(chessboard, block[WHITE][count_squareshape], CELL(x_temp,y_temp));
		if(count==0)
		{
			chessboard_place_block(chessboard, block[WHITE][count_squareshape], CELL(x_temp, y_temp));
			set_z_to_zero(chessboard, block[WHITE][count_squareshape], CELL(x_temp,y_temp));
		}
		break;
	case 2:
		reduce_z_regularly(chessboard, block[WHITE][count_ishape], CELL(x_temp,y_temp));
		if(count==0)
		{
			chessboard_place_block(chessboard, block[WHITE][count_ishape], CELL(x_temp, y_temp));
			set_z_to_zero(chessboard, block[WHITE][count_ishape], CELL(x_temp,y_temp));
			//count_ishape++;
		}
		break;
	case 3:
		reduce_z_regularly(chessboard, block[1][count_cube], CELL(x_temp,y_temp));
		if(count==0)
		{
			chessboard_place_block(chessboard, block[1][count_cube], CELL(x_temp, y_temp));
			set_z_to_zero(chessboard, block[1][count_cube], CELL(x_temp,y_temp));
			//count_ishape++;
		} 
		break;
	}
}
void timer(int extra) {
	glutPostRedisplay();
	// reduce_z(0.0);
	// glutTimerFunc(1000, reduce_z, 0);
	// reduce_z();
	glutTimerFunc(500, timer, 0);
	glutTimerFunc(500, update_game,0);	
}

void keypressed(unsigned char key, int x, int y) {
	if (key == 's') { viewer->pos[2]+=0.05; }
	if (key == 'w') { viewer->pos[2]-=0.05; }
	if (key == 'a') { viewer->pos[0]-=0.05; }
	if (key == 'd') { viewer->pos[0]+=0.05; }
	if (key == 'm') { viewer->pos[1]+=0.05; }
	if (key == 'n') { viewer->pos[1]-=0.05; }
	if (key == 'f') { highlight_cell_left(chessboard); }
	if (key == 'g') { highlight_cell_down(chessboard); }
	if (key == 'h') { highlight_cell_right(chessboard); }
	if (key == 't') { highlight_cell_up(chessboard); }
	if (key == 'p') { select_cell(chessboard, CELL_CURRENT); }
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


