#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string.h>
#include <stdlib.h>
#include <SOIL.h>
#include "base.h"
#include "block.h"
// #include "placer.h"
#include "viewer.h"
#include "glm.h"
#include <stdbool.h>
#include "AL/alut.h"
// #include <conio>
// #include <al/al.h>
#include <AL/alc.h>
// #include <al/alu.h>

#include <stdio.h>
#include <stdlib.h>  
#include <jpeglib.h>
#include <jerror.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#define HEIGHT 800
#define WIDTH 1200
#define NUM_TEXTURES 2
#define X_axis 50
#define Y_axis 51
#define Z_axis 52
#define clkwise 1
#define antclkwise -1

int texture[5];
Tetris_board *tetris_board;
Block *block[4]; 
Block *temp_block;
GLfloat ambientLightA[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuseLightA[4] = { 0.0f, 0.0f, 0.3f, 1.0f };

GLfloat ambientLightB[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat diffuseLightB[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

GLfloat specularLightA[4] = { 0.3f, 0.3f, 0.3f, 0.4f };
GLfloat specularLightB[4] = { 0.0f, 0.0f, 0.0f, 0.4f };

GLfloat lightPositionA[4] = { -100.0f, 100.0f, -100.0f, 1.0f };
GLfloat lightPositionB[4] = {  100.0f, 100.0f, 100.0f, 1.0f };

// GLfloat diffuseLightA[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
Viewer *viewer;

int time_status=0,time_count=0,isClicked_right,isClicked_left,flag=1,temp=0;
float height=0.8;				
// int x_temp,y_temp;
int color_block,speed=50;
int board_status[8][8],view_status[8][8][10],created_status[8][8],placed_status[8][8][10];
int music=1,is_ready_to_update_status_of_block=1,executed=1;
Block *current_block, *current_block_array[4];
// Block *next_block;
int next_block_type= 1;
BlockType global_type_block;
ALuint buffer, source;
int x[4],y[4],z[4]; 
int global_type=1,mode,speed_control=250;		
bool allow_movement;
int camera=0;

void loadSound(char* filename){		
	buffer = alutCreateBufferFromFile(filename);	
	alGenSources(1, &source);		
	alSourcei(source, AL_BUFFER, buffer);		
}			

void playSound(){		
	alSourcePlay(source);		
}

void drawText(const char *text, int length, int x, int y){
	 glMatrixMode(GL_PROJECTION); // change the current matrix to PROJECTION
	 double matrix[16]; // 16 doubles in stack memory
	 glGetDoublev(GL_PROJECTION_MATRIX, matrix); // get the values from PROJECTION matrix to local variable
	 glColor3f(0,0,0);
	 glLoadIdentity(); // reset PROJECTION matrix to identity matrix
	 glOrtho(0, 800, 0, 600, -5, 5); // orthographic perspective
	 glMatrixMode(GL_MODELVIEW); // change current matrix to MODELVIEW matrix again
	 glLoadIdentity(); // reset it to identity matrix
	 glPushMatrix(); // push current state of MODELVIEW matrix to stack
	 glLoadIdentity(); // reset it again. (may not be required, but it my convention)
	 glColor3f(0.0, 0.0, 0.0);
	 glRasterPos2i(x, y); // raster position in 2D
	 int i;
	 for(i=0; i<length; i++){
	  	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]); // generation of characters in our text with 9 by 15 GLU font
		}
	 glPopMatrix(); // get MODELVIEW matrix value from stack
	 glMatrixMode(GL_PROJECTION); // change current matrix mode to PROJECTION
	 glLoadMatrixd(matrix); // reset
	 glMatrixMode(GL_MODELVIEW); // change current matrix mode to MODELVIEW
}

//---------------------------------------------
// Texture timepass

typedef struct Image {
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
} Image;

int LoadGLTextures() {
	/* load an image file directly as a new OpenGL texture */
    texture[0] = SOIL_load_OGL_texture(	"texture/serenity.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    texture[1] = SOIL_load_OGL_texture(	"texture/circuit.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    // texture[2] = SOIL_load_OGL_texture(	"texture/back.jpg",
    //     SOIL_LOAD_AUTO,
    //     SOIL_CREATE_NEW_ID,
    //     SOIL_FLAG_INVERT_Y
    //     );
    // texture[3] = SOIL_load_OGL_texture(	"texture/right.jpg",
    //     SOIL_LOAD_AUTO,
    //     SOIL_CREATE_NEW_ID,
    //     SOIL_FLAG_INVERT_Y
    //     );
    // texture[4] = SOIL_load_OGL_texture(	"texture/top.jpg",
    //     SOIL_LOAD_AUTO,
    //     SOIL_CREATE_NEW_ID,
    //     SOIL_FLAG_INVERT_Y
    //     );
    // texture[5] = SOIL_load_OGL_texture(	"texture/bottom.jpg",
    //     SOIL_LOAD_AUTO,
    //     SOIL_CREATE_NEW_ID,
    //     SOIL_FLAG_INVERT_Y
    //     );

 
    if(!(texture[0] && texture[1] /*&& texture[2] && texture[3] && texture[4] && texture[5]*/)) {
    	printf("Unable to load Texture");
        return false;
    }
 
 
    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    // glBindTexture(GL_TEXTURE_2D, texture[3]);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    // glBindTexture(GL_TEXTURE_2D, texture[4]);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    // glBindTexture(GL_TEXTURE_2D, texture[1]);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    // glBindTexture(GL_TEXTURE_2D, texture[5]);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    return true;                                        // Return Success
}

void init() {
	tetris_board = create_tetris_board();
	viewer = create_viewer((Placeable *)tetris_board);
	int i,j,k;
	for ( i = 0; i < 8; ++i)
	{
		for ( j = 0; j < 8; ++j)
		{
			board_status[i][j]=0;
			for ( k = 0; k < 10; k++)
			{
				view_status[i][j][k]=0;
				placed_status[i][j][k]=0;
				// block[i][j][k] = create_block(ishape, 1);
			}
		}
	}
	block[0]=create_block(type1,color_block);
	block[1]=create_block(type2,color_block);
	block[2]=create_block(type3,color_block);
	block[3]=create_block(type4,color_block);
	tetris_board->score=0;
	glClearColor (0.8, 0.8, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
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
int save_screenshot(char* filename, int w, int h)
{	
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	int nSize = w*h*3;
	char* dataBuffer = (char*)malloc(nSize*sizeof(char));
	if (!dataBuffer) return 0;
	glReadPixels((GLint)0, (GLint)0,(GLint)w, (GLint)h,GL_BGR, GL_UNSIGNED_BYTE, dataBuffer);
	FILE *filePtr = fopen(filename, "wb");
	if (!filePtr) return 0;
	unsigned char TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
	unsigned char header[6] = { w%256,w/256,h%256,h/256,24,0};
	fwrite(TGAheader,	sizeof(unsigned char),	12,	filePtr);
	fwrite(header,	sizeof(unsigned char),	6,	filePtr);
	fwrite(dataBuffer,	sizeof(GLubyte),	nSize,	filePtr);
	fclose(filePtr);
	return 1;
}

void display() {
	if (!LoadGLTextures())								// Jump To Texture Loading Routine ( NEW )
	{
		printf("Not loaded texture!\n");
		// return FALSE;									// If Texture Didn't Load Return FALSE
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

	glViewport(0, 0, WIDTH/2+200, HEIGHT);
	observe_from_viewer(viewer);
	display_tetris_board(tetris_board,board_status,created_status,view_status,placed_status);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		// glTranslatef(0.0,0.0,-2.0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		GLUquadricObj *quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL );
		gluQuadricNormals(quadric, GLU_SMOOTH);
		gluQuadricTexture(quadric, GL_TRUE);
		// glEnable(GL_TEXTURE_2D);
		gluSphere( quadric ,20, 16 , 9 );
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		DrawBase();
		// glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glViewport(WIDTH/2+300, 0, 300, HEIGHT);
	glPushMatrix();
		char buf[4]={'\0'};
		char out[6];
		glDisable(GL_LIGHTING);
		
		sprintf(buf, "%d", 50-speed);
		drawText("Speed: ",strlen("Score: "),0,180);
		drawText(buf,strlen(buf), 200, 180);
		
		// if(next_block_type==0)
		// {
		// 	// block_temp=block[0];
			
		// }
		// else if(next_block_type==1)
		// {
		// 	block_temp=block[1];
		// 	// temp=type2;
		// }
		// else if(next_block_type==2)
		// {
		// 	block_temp=block[2];
		// 	// temp=type3;
		// }
		// else if( next_block_type==3)
		// {
		// 	block_temp=block[3];
		// 	// temp=type4;
		// }
		sprintf(buf, "%d", tetris_board->score);
		drawText("Score: ",strlen("Score: "),0,200);
		drawText(buf,strlen(buf), 200, 200);


		sprintf(buf, "%d", next_block_type);
		drawText("Next Block Type: ",strlen("Next Block Type: "),0,220);
		drawText(buf,strlen(buf), 500, 220);

		// sprintf(buf, "", next_block_type);
		// drawText("Next Block Name: ",strlen("Next Block Name: "),0,240);
		// drawText(buf,strlen(buf), 500, 240);

		// sprintf(buf, "%d", next_block_type);
		drawText("Camera : Keyboard(ASWD)",strlen("Camera : Keyboard(ASWD)"),0,40);
		// drawText(buf,strlen(buf), 500, 220);

		// sprintf(buf, "%d", next_block_type);
		drawText("Camera:Mouse(Lft & Rht Click",strlen("Camera:Mouse(Lft & Rht)"),0,60);
		// drawText(buf,strlen(buf), 500, 260);
		drawText("Screenshot : Z",strlen("Screenshot : Z"),0,80);
		drawText("Rotation(R,T,Y)",strlen("Rotation(R,T,Y)"),0,100);
		drawText("Exit : X",strlen("Exit : X"),0,160);
		drawText("Move Down : Spacebar",strlen("Move Down : Spacebar"),0,140);
		drawText("Music : M",strlen("Music : M"),0,120);


		glEnable(GL_LIGHTING);
	glPopMatrix();
	// Block *block_temp;
	// // BlockType temp;
	// // // if(temp)
	// // block=create_block(squareshape,color_block);
	// // glScalef(2,2,2);
	glViewport(WIDTH/2+200, HEIGHT/2, 300, HEIGHT/2);
	glPushMatrix();

 //     draw block
 //    glTranslated(block_temp->pos[0], block_temp->pos[1], block_temp->pos[2]);
	// glScalef(block_temp->width, block_temp->height, block_temp->width);

 //    if (block_temp->model) {
	// 		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, block_temp->color);
	// 		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, block_temp->color);
	// 		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, block_temp->color);
	// 		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.5f);
 //        	glmDraw(block_temp->model, GLM_SMOOTH);
 //    }
    glPopMatrix();
	// glPushMatrix ();

	// 	glTranslatef (-1, -1, 0);
	// 	glLoadIdentity();
	// 	glColor4f(0.2,0.2,0.2,0.6);
	// 	GLUquadricObj *quadric1;
	// 	quadric = gluNewQuadric();
	// 	gluQuadricDrawStyle(quadric1, GLU_FILL );
	// 	// glBindTexture (GL_TEXTURE_2D, textures[3]);
	// 	glTranslatef(-0.45,0,0);
	// 	gluSphere( quadric1 , .3 , 36 , 18 );
	// 	glTranslatef(0.45,0,0);
	// 	gluSphere( quadric1 , .3 , 36 , 18 );
		// glutSolidTeapot(0.5);
	// glPopMatrix ();
	glFlush();	

	glutSwapBuffers();
}

void reshape (int w, int h) {
	glViewport (0, 0, w, h);
	// glViewport (0, 0, 1000, h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

int **rotate(int inp[][4], int dir, int axis, int num){
	printf("entered rotate function by purswani\n");
	int Rx[4][4] = {{1,0,0,0},{0,0,-1*dir,0},{0,1*dir,0,0},{0,0,0,1}};
	int Ry[4][4] = {{0,0,1*dir,0},{0,1,0,0},{-1*dir,0,0,0},{0,0,0,1}};
	int Rz[4][4] = {{0,-1*dir,0,0},{1*dir,0,0,0},{0,0,1,0},{0,0,0,1}};

	int R_temp[4][4];
	switch(axis){
		case X_axis:
			memcpy(R_temp, Rx, sizeof(int) * 4 * 4);
			break;
		case Y_axis:
			memcpy(R_temp, Ry, sizeof(int) * 4 * 4);
			break;
		case Z_axis:
			memcpy(R_temp, Rz, sizeof(int) * 4 * 4);
			break;
		defualt:
			return;
	}
	
	int **res;
	int i,j,k;
	res = (int**)calloc(4,sizeof(int*));
	for(i=0;i<4;i++) res[i] = (int*)calloc(num,sizeof(int));

	int mat[4][num];
	for(i=0;i<4;i++) for(j=0;j<num;j++) mat[i][j] = inp[j][i];
	for(i=0;i<4;i++){
		for(j=0;j<num;j++) printf("%d ",mat[i][j]);
		putchar('\n');
	}
	putchar('\n');
	
	int min=INT_MAX,max=INT_MIN;
	int tx,ty,tz;

	for(i=0;i<num;i++){
		if(mat[0][i]>max) max = mat[0][i];
		if(mat[0][i]<min) min = mat[0][i];
	}
	tx = (max+min)/2;
	min=INT_MAX,max=INT_MIN;
	for(i=0;i<num;i++){
		if(mat[1][i]>max) max = mat[1][i];
		if(mat[1][i]<min) min = mat[1][i];
	}
	ty = (max+min)/2;
	min=INT_MAX,max=INT_MIN;
	for(i=0;i<num;i++){
		if(mat[1][i]>max) max = mat[2][i];
		if(mat[1][i]<min) min = mat[2][i];
	}
	tz = (max+min)/2;
	min=INT_MAX,max=INT_MIN;
	//printf("%d %d %d\n",tx,ty,tz);

	int T[4][4] = {1,0,0,-tx,0,1,0,-ty,0,0,1,-tz,0,0,0,1};	
	int Tb[4][4] = {1,0,0,tx,0,1,0,ty,0,0,1,tz,0,0,0,1};	

	int res2[4][4];
	int res1[4][4];
	for(i=0;i<4;i++) for(j=0;j<4;j++) res2[i][j]=0;
	for(i=0;i<4;i++) for(j=0;j<4;j++) res1[i][j]=0;

	for(i=0;i<4;i++) for(j=0;j<4;j++) for(k=0;k<4;k++) res2[i][j]+=Tb[i][k]*R_temp[k][j];
	for(i=0;i<4;i++) for(j=0;j<4;j++) for(k=0;k<4;k++) res1[i][j]+=res2[i][k]*T[k][j];
	for(i=0;i<4;i++) for(j=0;j<num;j++) for(k=0;k<4;k++) res[i][j]+=res1[i][k]*mat[k][j];
	//for(i=0;i<4;i++){
	//	for(j=0;j<4;j++) printf("%d ",R[i][j]);
	//	putchar('\n');
	//}
	//putchar('\n');
	printf("exied rotate function by purswani\n");

	return res;
}

void check_game_over()
{
	int i;
	for ( i = 0; i < 4; ++i)
	{
		if(board_status[x[i]][y[i]]>=8)
		{
			printf("Game Over\n");
			printf("\n\nYour total score is %d\n",tetris_board->score );
			exit(0);
		}
	}
}
void game_over()
{
	printf("Game Over\n");
	printf("\n\nYour total score is %d\n",tetris_board->score );
	exit(0);
}
bool collision()
{
	int i;
	for ( i = 0; i < 4; ++i)
	{
		if(board_status[x[i]][y[i]]>=z[i]) 
		{ 
			return true;
		}
	}
	return false;
}
void update_created_status(int k)
{
	int i;
	for ( i = 0; i < 4; ++i)
	{
		created_status[x[i]][y[i]]=k;
	}
}
void create_new_shape(int type,int color_block)
{
	int i,current_z;
	printf("Creating block\n");
	mode=0;
	if(type==1)
	{
		int temp_x=rand()%7;
		int temp_y=rand()%7;
		x[0]=x[2]=temp_x;
		x[1]=x[3]=temp_x+1;
		y[0]=y[1]=temp_y;
		y[2]=y[3]=temp_y+1;
		z[0]=z[1]=z[2]=z[3]=8;
		// x[4]={temp_x,temp_x+1,temp_x,temp_x+1};
		// y[4]={temp_y,temp_y,temp_y+1,temp_y+1};
		// z[4]={8,8,8,8};
	}
	else if(type==2)
	{
		int temp_x=rand()%6;
		int temp_y=rand()%7;
		x[0]=temp_x;
		x[1]=temp_x + 1;
		x[2]=x[3]=temp_x+2;
		y[3]=temp_y;
		y[0]=y[1]=y[2]=temp_y+1;
		z[0]=z[1]=z[2]=z[3]=8;
	}
	else if(type==3)
	{
		int temp_x=rand()%6;
		int temp_y=rand()%7;
		x[0]=temp_x;
		x[1]=x[3]=temp_x + 1;
		x[2]=temp_x+2;
		y[3]=temp_y;
		y[0]=y[1]=y[2]=temp_y+1;
		z[0]=z[1]=z[2]=z[3]=8;
	}
	else if(type==4)
	{
		int temp_x=rand()%5;
		int temp_y=rand()%8;
		x[0]=temp_x;
		x[1]=temp_x + 1;
		x[2]=temp_x + 2;
		x[3]=temp_x + 3;
		y[0]=y[1]=y[2]=y[3]=temp_y;
		z[0]=z[1]=z[2]=z[3]=8;		
	}
	for ( i = 0; i < 4; ++i)
	{
		current_block=create_block(squareshape, color_block);
		// current_blockx=set_block(global_type_block, color_block,current_block);
		tetris_board_place_block(tetris_board,current_block, CELL(x[i], y[i],z[i]),z[i]);
		// view_status[x[i]][y[i]][z[i]]=1;
	}

}
//To move the block by 0.1 units downward
void move_down()
{
	int i,j;
	check_game_over();
	printf("moved down 1 step\n");
	if(executed==1)
	{
		for ( i = 0; i < 4 ; ++i)
		{
			if(z[i]==0) return;
		}
		for ( i = 0; i < 4 ; ++i)
		{
			current_block=tetris_board->board[CELL(x[i], y[i],z[i])];
			view_status[x[i]][y[i]][z[i]]=0;
			z[i]--;
			view_status[x[i]][y[i]][z[i]]=1;
			// current_block=set_block(global_type_block, color_block,current_block);
			tetris_board_place_block_at_boardvalue(tetris_board,current_block, CELL(x[i], y[i],z[i]),z[i]);
		}
	}
	else
	{
		printf("executed =0\n");;
	}
	printf("moved 1 step\n");

}
void fix_block_at_z()
{
	int i; 
	for ( i = 0; i < 4; ++i)
	{
		// current_z=board_status[x[i]][y[i]];
		current_block=tetris_board->board[CELL(x[i], y[i],z[i])];
		tetris_board_place_block_at_boardvalue(tetris_board,current_block, CELL(x[i], y[i],z[i]),z[i]);
		printf("Block placed at x=%f,y=%f and z=%f\n",current_block->pos[0],current_block->pos[2],current_block->pos[1] );
	}
}


//Update board status by 1 i.e now the blocks should come above the already placed block
void increment_board_status(int type)
{
	if(!collision()) return;
	printf("Updating board status\n");
	int i,j;
	// if(type==1)
	// {
		for ( i = 0; i < 4; ++i)
		{
			board_status[x[i]][y[i]]=z[i]+1;
			view_status[x[i]][y[i]][z[i]]=1;
			placed_status[x[i]][y[i]][z[i]]=1;
		}
	// }
	for(i=0;i<4;++i)
	{
		printf("x = %d,y=%d,z=%d,board_status=%d,view_prev=%dand viewstatus=%d\n",x[i],y[i],z[i],board_status[x[i]][y[i]],view_status[x[i]][y[i]][z[i]-1],view_status[x[i]][y[i]][z[i]] );
	}
}

//The main code is implemented here
void update_game()
{
	int type,i;
	check_game_over();
	global_type_block=squareshape;
	if(flag==1)
	{ 
		allow_movement=true;
		printf("\n\n");
		flag=0;
		// count=height/0.1;
		type= next_block_type;
		next_block_type= rand()%4 +1;
		// next_block_type=1;
		// type=2;
		global_type=type;
		color_block=rand()%3;
		printf("Creating the blocks\n");
		create_new_shape(type,color_block);
		update_created_status(1);
	}
	if(collision())
	{
		allow_movement=false;
		for ( i = 0; i < 4; ++i)
		{
			if(z[i]==8)
			{
				game_over();
			}
		}
		printf("type==%d\n",global_type );
		// fix_block_at_z();
		if(!collision())
		{
			allow_movement=true;
			move_down();
			return;
		}
		increment_board_status(global_type); 
		update_created_status(0);
		tetris_board->score+=5;
		printf("\nScore==%d\n",tetris_board->score );
		check_game_over();
		// for(i=0;i<4;++i)
		// {
		// 	printf("z==%f\n",tetris_board->board[CELL(x[i], y[i],0)]->pos[1] );
		// }
		flag=1;
	}
	else
	{
		move_down();
	}
}

void move_block_max_down()
{
	int i;
	while(!collision())
	{
		for ( i = 0; i < 4 ; ++i)
		{
			if(z[i]==0) goto a;
		}
		move_down();
		tetris_board->score+=5;
	}
	a : for ( i = 0; i < 4; ++i)
	{
		if(z[i]==8)
		{
			game_over();
		}
	}
	increment_board_status(global_type);
	update_created_status(0);
	printf("\nScore==%d\n",tetris_board->score );
	check_game_over();
	flag=1;
}
int max(int a,int b)
{
	if(a>b) return a;
	return b;
}
int min(int a , int b)
{
	if(a<b) return a;
	return b;
}
void move_block_right()
{
	executed=0;
	int i;
	bool check=true;
	for ( i = 0; i < 4; ++i)
	{
		if((x[i]>6) || ((view_status[x[i]+1][y[i]][z[i]]==1)&&((x[i]+1)!=x[0])&&((x[i]+1)!=x[2])&&((x[i]+1)!=x[3])&&((x[i]+1)!=x[1]))) 
		{
			check=false;
		}
	}
	if(check)   
	{
		update_created_status(0);
		for (i=0;i<4;i++)
		{
			view_status[x[i]][y[i]][z[i]]=0;
			current_block_array[i]=tetris_board->board[CELL(x[i], y[i],z[i])];
		}
		for (i=0;i<4;i++)
		{
			x[i]++;
			view_status[x[i]][y[i]][z[i]]=1;
			tetris_board_place_block_at_boardvalue(tetris_board,current_block_array[i], CELL(x[i], y[i],z[i]),z[i]);
		}
		printf("moving right\n");
		update_created_status(1);
	}
	executed=1;
}
void move_block_left()
{
	executed=0;
	int i;
	bool check=true;
	for ( i = 0; i < 4; ++i)
	{
		if((x[i]<1) || ((view_status[x[i]-1][y[i]][z[i]]==1)&&((x[i]-1)!=x[0])&&((x[i]-1)!=x[2])&&((x[i]-1)!=x[3])&&((x[i]-1)!=x[1]))) 
		{
			check=false;
		}
	}
	if(check)   
	{
		update_created_status(0);
		for (i=0;i<4;i++)
		{
			view_status[x[i]][y[i]][z[i]]=0;
			current_block_array[i]=tetris_board->board[CELL(x[i], y[i],z[i])];
		}
		for (i=0;i<4;i++)
		{
			x[i]--;
			view_status[x[i]][y[i]][z[i]]=1;
			tetris_board_place_block_at_boardvalue(tetris_board,current_block_array[i], CELL(x[i], y[i],z[i]),z[i]);
		}
		printf("moving left\n");
		update_created_status(1);
	}
	executed=1;
}
void move_block_up()
{
	executed=0;
	int i;
	bool check=true;
	for ( i = 0; i < 4; ++i)
	{
		if(y[i]>6  || ((view_status[x[i]][y[i]+1][z[i]]==1)&&((y[i]+1)!=y[0])&&((y[i]+1)!=y[2])&&((y[i]+1)!=y[3])&&((y[i]+1)!=y[1])))
		{
			check=false;
		}
	}
	if(check)   
	{
		update_created_status(0);
		for (i=0;i<4;i++)
		{
			view_status[x[i]][y[i]][z[i]]=0;
			current_block_array[i]=tetris_board->board[CELL(x[i], y[i],z[i])];
		}
		for (i=0;i<4;i++)
		{
			y[i]++;
			view_status[x[i]][y[i]][z[i]]=1;
			tetris_board_place_block_at_boardvalue(tetris_board,current_block_array[i], CELL(x[i], y[i],z[i]),z[i]);
		}
		printf("moving up\n");
		update_created_status(1);
	}
	executed=1;
}
void move_block_down()
{
	executed=0;
	int i;
	bool check=true;
	for ( i = 0; i < 4; ++i)
	{
		if(y[i]<1  || ((view_status[x[i]][y[i]-1][z[i]]==1)&&((y[i]-1)!=y[0])&&((y[i]-1)!=y[2])&&((y[i]-1)!=y[3])&&((y[i]-1)!=y[1])))
		{
			check=false;
		}
	}
	if(check)   
	{
		update_created_status(0);
		for (i=0;i<4;i++)
		{
			view_status[x[i]][y[i]][z[i]]=0;
			current_block_array[i]=tetris_board->board[CELL(x[i], y[i],z[i])];
		}
		for (i=0;i<4;i++)
		{
			y[i]--;
			view_status[x[i]][y[i]][z[i]]=1;
			tetris_board_place_block_at_boardvalue(tetris_board,current_block_array[i], CELL(x[i], y[i],z[i]),z[i]);
		}
		printf("moving up\n");
		update_created_status(1);
	}
	executed=1;
}

void rotate_try(int axis)
{
	int i,j,xnew[4],ynew[4],znew[4];
	int mat[4][4];
	printf("Entered rotate_try()\n");
	if(global_type==1)
	{
		// printf("ent\n");
		if(((mode%3 ==1) && x[0]>6 && x[2]>6 ) || ((mode%3==0) && z[0]>6 && z[2]>6) || ( mode%3==2 && x[0]>6 && y[0]>6) )
		{
			printf("returned in type=1\n");
			return;
		}
		for ( i = 0; i < 4; ++i)
		{
			xnew[i]=x[i];
			ynew[i]=y[i];
			znew[i]=z[i];
		}
		if((mode%3==2) &&  (view_status[x[0]][y[0]+1][z[0]]!=1) && (view_status[x[0]+1][y[0]+1][z[0]]!=1) )
		{
			// int xnew[4]={x[0],x[0]+1,x[0],x[0]+1};
			// int ynew[4]={y[0],y[0],y[2],y[2]};
			// int znew[4]={z[0],z[0],z[0],z[0]};
			// xnew[0]=xnew[2]=x[0];
			// xnew[1]=xnew[3]=x[0]+1;
			// ynew[0]=ynew[1]=y[0];
			// ynew[2]=ynew[3]=y[2];
			// znew[0]=znew[1]=znew[2]=znew[3]=z[0];
			xnew[0]=xnew[2]=x[0];
			xnew[1]=xnew[3]=x[0]+1;
			ynew[0]=ynew[1]=y[0];
			ynew[2]=ynew[3]=y[0]+1;
			znew[0]=znew[1]=znew[2]=znew[3]=z[0];

		}
		else if((mode%3==0) && (view_status[x[0]][y[0]][z[0]+1]!=1) && (view_status[x[2]][y[2]][z[2]+1]!=1) )
		{
			// int xnew[4]={x[0],x[0],x[2],x[2]};
			// int ynew[4]={y[0],y[0],y[2],y[2]};
			// int znew[4]={z[0],z[0]+1,z[2],z[2]+1};
			// printf("old coordunates are \n");
			xnew[0]=xnew[1]=x[0];
			xnew[3]=xnew[2]=x[2];
			ynew[0]=ynew[1]=y[0];
			ynew[2]=ynew[3]=y[2];
			znew[0]=z[0];
			znew[2]=z[2];
			znew[1]=z[0]+1;
			znew[3]=z[2]+1;

		}
		else if((mode%3==1) && (view_status[x[0]+1][y[0]][z[0]+1]!=1) && (view_status[x[0]+1][y[0]][z[0]+1]!=1) )
		{
			xnew[3]=xnew[2]=x[0]+1;
			ynew[3]=ynew[2]=y[0];
		}
		else
		{
			return;
		}
		for ( i = 0; i < 4; ++i)
		{
			printf("Old coordinates are (%d,%d,%d)\n",x[i],y[i],z[i] );
		}
		for ( i = 0; i < 4; ++i)
		{
			printf("New coordinates are (%d,%d,%d)\n",xnew[i],ynew[i],znew[i] );
		}
		update_created_status(0);
		for ( i = 0; i < 4; ++i)
		{
			view_status[x[i]][y[i]][z[i]]=0;
			// tetris_board->board[CELL(x[i], y[i],z[i])]=NULL;
			current_block_array[i]=tetris_board->board[CELL(x[i], y[i],z[i])];
		}
		for ( i = 0; i < 4; ++i)
		{
			x[i]=xnew[i];
			y[i]=ynew[i];
			z[i]=znew[i];
			// printf("check 1\n");
			view_status[x[i]][y[i]][z[i]]=1;
			tetris_board_place_block_at_boardvalue(tetris_board,current_block_array[i], CELL(x[i], y[i],z[i]),z[i]);
		}
		update_created_status(1);
		mode++;
		printf("mode changed to %d\n",mode%2);
	}

	// else if(global_type==2)
	// {

	// }
	else 
	{
		int num=4;
		executed=0;
		// int mat[][4] = {{6,1,6,1},{7,1,6,1},{6,2,6,1},{7,2,6,1}};

		for ( i = 0; i < 4; ++i)
		{
			mat[i][0]=x[i];
			mat[i][1]=y[i];
			mat[i][2]=z[i];
			mat[i][3]=1;
			if(z[i]==0) goto b;

		}
		int **res = rotate(mat,antclkwise,axis,num);
		int i,j;
		for(i=0;i<4;i++)
		{
			for(j=0;j<num;j++) printf("%d ",res[i][j]);
			putchar('\n');
		}
		for(i=0;i<4;i++)
		{
			if(res[0][i]<0 || res[0][i]>7 || res[1][i]<0 || res[1][i]>7 || res[2][i]<0 || res[2][i]>7)
			{
				printf("retunred\n");
				goto b;
			}
		}

		printf("\n");
		update_created_status(0);
		bool l;
		for(i=0;i<4;i++)
		{
			if((view_status[res[0][i]][res[1][i]][res[2][i]]==1)  )
			{
				l=true;
				for(j=0;j<4;j++)
				{
					if((res[0][j]==x[j] && res[1][j]==y[j] && res[2][j]==z[j]))
					{
						l=false;
					}
				}
				if(l==true) 
				{
					printf("can't be\n");
					goto b;
				}
			}
		}
		printf("possible\n");
		for ( i = 0; i < 4; ++i)
		{
			if(view_status[x[i]][y[i]][z[i]]==0)
			{
				printf("Impossible\n");
				printf("x=%d,y=%d,z=%d and view_sattus=%d\n",x[i],y[i],z[i], view_status[x[i]][y[i]][z[i]]);
			}
			view_status[x[i]][y[i]][z[i]]=0;
			// current_block_array[i]=tetris_board->board[CELL(x[i], y[i],z[i])];
		}
		// printf("hi\n");
		// for(i=0;i<4;i++)
		// {
		// 	if((view_status[res[0][i]][res[1][i]][res[2][i]]==1)  )
		// 	{
		// 		for ( i = 0; i < 4; ++i)
		// 		{
		// 			view_status[x[i]][y[i]][z[i]]=1;
		// 			tetris_board->board[CELL(x[i], y[i],z[i])]=current_block_array[i];
		// 			update_created_status(1);
		// 		}
		// 		return;
		// 	}
		// }
		for ( i = 0; i < 4; ++i)
		{
			x[i]=res[0][i];
			y[i]=res[1][i];
			z[i]=res[2][i];
			view_status[x[i]][y[i]][z[i]]=1;
			current_block_array[i]=create_block(squareshape, color_block);
			tetris_board_place_block_at_boardvalue(tetris_board,current_block_array[i], CELL(x[i], y[i],z[i]),z[i]);
			printf("x=%d,y=%d,z=%d and view_sattus=%d\n",x[i],y[i],z[i], view_status[x[i]][y[i]][z[i]]);
			// putchar('\n');
		}
		b:
		update_created_status(1);
		executed=1;
		// for ( i = 0; i < 4; ++i)
		// {
		// }
		// for(i=0;i<4;i++)
		// {
		// 	// for(j=0;j<3;j++)
		// 	// {
		// 		// printf("x=%d,y=%d,z=%d \n",res[0][i],res[1][i],res[2][i]);
		// 	// }
		// }
		// mode++;
		// printf("mode changed to %d\n",mode%2);
	}
}



void timer(int extra) {
	glutPostRedisplay();
	while(!executed);
	while(time_status>=speed)
	{
		time_status=0;
		update_game();
	}
	if(time_count%speed_control==0)
	{
		speed--;
		speed_control+=50+speed_control;
		printf("speed increased\n");
	}
	time_count++;
	time_status++;
	glutTimerFunc(1, timer, 0);
	// glutTimerFunc(200, update_game,0);	
	// glutTimerFunc(200, update_game,0);	
}

void keypressed(unsigned char key, int x, int y) {
	if (key == 's') { viewer->pos[2]+=0.05; }
	if (key == 'w') { viewer->pos[2]-=0.05; }
	if (key == 'a') { viewer->pos[0]-=0.05; }
	if (key == 'd') { viewer->pos[0]+=0.05; }
	if (key == 'b') { viewer->pos[1]+=0.05; }
	if (key == 'n') { viewer->pos[1]-=0.05; }
	if (key == 'z') { save_screenshot("a.tga",WIDTH,HEIGHT); }
	if( key == 'r') {rotate_try(X_axis);}
	if( key == 't') {rotate_try(Y_axis);}
	if( key == 'y') {rotate_try(Z_axis);}
	if (key == 'x') 
	{ 
		printf("\n\nYour total score is %d\n",tetris_board->score );
		exit(0);
	}
	if( key == ' ')
	{
		move_block_max_down();
	}
	if (key=='m')
	{
		if(music==0){
			alSourceStop(source);
			music=1;
		}
		else
		{
			loadSound("./wav/theme.wav");
			alSourcePlay(source);
			music=0;
		}
	}

}

void move_camera()
{
	if(camera % 4 ==0)
	{
		viewer->pos[0]=0.0;
		viewer->pos[2]=0.85;
	}
	else if (camera % 4 == 1)
	{
		viewer->pos[0]=-0.85;
		viewer->pos[2]=0.0;
	}
	else if( camera % 4 ==2)
	{
		viewer->pos[0]=0.0;
		viewer->pos[2]=-0.85;
	}
	else if( camera % 4 ==3)
	{
		viewer->pos[0]=0.85;
		viewer->pos[2]=0.0;
	}

}
void keypressSpecial(int key, int x, int y){
	if (key == GLUT_KEY_UP) {
		loadSound("./wav/tick.wav"); playSound();
		// if(!collision())
		if(allow_movement)
		{
			if(camera % 4==3 ) move_block_left();
			else if(camera % 4==1 ) move_block_right();
			else if (camera % 4==2 ) move_block_down();
			else if( camera % 4==0 ) move_block_up();
		}
		// move_block_up();
	}
	if (key== GLUT_KEY_DOWN){
		loadSound("./wav/tick.wav"); playSound();
		// if(allow_movement)
		// move_block_down();
		if(allow_movement)
		{
			if(camera % 4==1 ) move_block_left();
			else if(camera % 4==3 ) move_block_right();
			else if (camera % 4==0 ) move_block_down();
			else if( camera % 4==2 ) move_block_up();
		}
	}
	if (key== GLUT_KEY_LEFT){
		loadSound("./wav/tick.wav"); playSound();
		// if(allow_movement)
		// move_block_left();
		if(allow_movement)
		{
			if(camera % 4==0 ) move_block_left();
			else if(camera % 4==2 ) move_block_right();
			else if (camera % 4==3 ) move_block_down();
			else if( camera % 4==1 ) move_block_up();
		}
	}
	if (key== GLUT_KEY_RIGHT){
		loadSound("./wav/tick.wav"); playSound();
		// if(allow_movement)
		// move_block_right();
		if(allow_movement)
		{
			if(camera % 4==2 ) move_block_left();
			else if(camera % 4==0 ) move_block_right();
			else if (camera % 4==1 ) move_block_down();
			else if( camera % 4==3 ) move_block_up();
		}

	}

}
void mouseMove(int x, int y) 
{ 	
	// if (isClicked_left) { 
	// 	viewer->pos[2]-=0.05;
	// }
	// else if (isClicked_right)
	// {
	// 	viewer->pos[2]+=0.05;
	// }
	if(viewer->pos[2]<0 && viewer->pos[0] > 0 )
	{

	}
	if(viewer->pos[2]<0 && viewer->pos[0] > 0 )
	{

	}
	if(viewer->pos[2]<0 && viewer->pos[0] > 0 )
	{

	}
	if(viewer->pos[2]<0 && viewer->pos[0] > 0 )
	{

	}
}
void mouseButton(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON) 
	{
		if (state == GLUT_DOWN) { 
			// viewer->pos[2]-=0.05;
			// isClicked_left=1;
			camera++;
			move_camera();
		}
		else  { 
			isClicked_left = 0; 
		}

	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			// viewer->pos[2]+=0.05;
			// isClicked_right=1;
			camera--;
			move_camera();
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
	printf("viewer == (%f,%f)\n", viewer->pos[0],viewer->pos[2] );
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	alutInit (&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize (1200, 1000);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("3D-Tetris");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keypressed);
	glutSpecialFunc(keypressSpecial);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	glutTimerFunc(0,timer,0);

	init();
	glutMainLoop();

	end();

	return 0;
}


