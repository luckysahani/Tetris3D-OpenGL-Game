#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string.h>
#include <stdlib.h>

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

#define HEIGHT 600
#define WIDTH 1000
#define NUM_TEXTURES 2
Tetris_board *tetris_board;
Block *block[8][8][6]; 
Block *temp_block;
GLfloat ambientLightA[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuseLightA[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat ambientLightB[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat diffuseLightB[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

GLfloat specularLightA[4] = { 0.3f, 0.3f, 0.3f, 0.4f };
GLfloat specularLightB[4] = { 0.0f, 0.0f, 0.0f, 0.4f };

GLfloat lightPositionA[4] = { -100.0f, 100.0f, -100.0f, 1.0f };
GLfloat lightPositionB[4] = {  100.0f, 100.0f,  100.0f, 1.0f };

// GLfloat diffuseLightA[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
//-----------------------------------------------------------------
Viewer *viewer;

int time_status=0,time_count=0,isClicked_right,isClicked_left,flag=1,temp=0;
float height=0.8;				
// int x_temp,y_temp;
int color_block,speed=50;
int board_status[8][8],view_status[8][8][10],created_status[8][8],placed_status[8][8][10];
int music=1,is_ready_to_update_status_of_block=1,executed=1;
Block *current_block, *current_block_array[4];
GLuint texture;
BlockType global_type_block;
ALuint buffer, source;
int x[4],y[4],z[4]; 
int global_type=1,mode;		
bool allow_movement;

// Some variables for textures
static float	plane_xy[3] = {1, 0, 0};
static float	plane_yz[3] = {0, 0, 1};

//---------------------------------------------------------
void loadSound(char* filename){		
	buffer = alutCreateBufferFromFile(filename);	
	alGenSources(1, &source);		
	alSourcei(source, AL_BUFFER, buffer);		
}
//----------------------------------------------------------			
void playSound(){		
	alSourcePlay(source);		
}

//----------------------------------------------------------
void init() {
/* the tetris_board and the table and the player (viewer)*/
	tetris_board = create_tetris_board();
	viewer = create_viewer((Placeable *)tetris_board);
	int i,j,k;
// itn k=0.0;
	for ( i = 0; i < 8; ++i)
	{
		for ( j = 0; j < 8; ++j)
		{
			board_status[i][j]=0;
			for ( k = 0; k < 10; k++)
			{
				view_status[i][j][k]=0;
				placed_status[i][j][k]=0;
				block[i][j][k] = create_block(ishape, 1);
			}
		}
	}
	tetris_board->score=0;
	glClearColor (0.8, 0.8, 1.0, 1.0);
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
//------------------------------------------------------
void end() {
	destroy_tetris_board(tetris_board);
	destroy_viewer(viewer);
}
//-------------------------------------------------------
/* Texture experiments going on here */

static GLuint textures[NUM_TEXTURES];
typedef struct {
	char* name;
	int format;
	unsigned int size;
}	texture_info_t;

void		Teapot (void)
{
  // glTranslatef (translate_x, 0, translate_y);
  glRotatef (-60, 0, 1, 0);
  glutSolidTeapot (0.4);
}

/*
** Function to load a Jpeg file.
*/
int		load_texture (const char * filename,
			      unsigned char * dest,
			      const int format,
			      const unsigned int size)
{
  FILE *fd;
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  unsigned char * line;

  cinfo.err = jpeg_std_error (&jerr);
  jpeg_create_decompress (&cinfo);

  if (0 == (fd = fopen(filename, "rb"))){
  	printf("Unable to open file: %s\n",filename);
    return 1;
  }

  jpeg_stdio_src (&cinfo, fd);
  jpeg_read_header (&cinfo, TRUE);
  if ((cinfo.image_width != size) || (cinfo.image_height != size))
    return 1;

  if (GL_RGB == format)
    {
      if (cinfo.out_color_space == JCS_GRAYSCALE)
	return 1;
    }
  else
    if (cinfo.out_color_space != JCS_GRAYSCALE)
      return 1;

  jpeg_start_decompress (&cinfo);

  while (cinfo.output_scanline < cinfo.output_height)
    {
      line = dest +
	(GL_RGB == format ? 3 * size : size) * cinfo.output_scanline;
      jpeg_read_scanlines (&cinfo, &line, 1);
    }
  jpeg_finish_decompress (&cinfo);
  jpeg_destroy_decompress (&cinfo);
  return 0;
}


//-------------------------------------------------------

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

//--------------------------------------------
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

//--------------------------------------------

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
	glViewport(0, 0, WIDTH/2+100, HEIGHT);
  	// Perspective Projection

	observe_from_viewer(viewer);
	display_tetris_board(tetris_board,board_status,created_status,view_status,placed_status);

	// Now we need orthgraphic view
 	// Lower left window
 	glViewport(WIDTH/2+200, 0, 300, HEIGHT);
	glPushMatrix();
		char buf[4]={'\0'};
		sprintf(buf, "%d", 50-speed);
		glDisable(GL_LIGHTING);
		drawText("Speed: ",strlen("Score: "),10,180);
		drawText(buf,strlen(buf), 200, 180);
		sprintf(buf, "%d", tetris_board->score);
		drawText("Score: ",strlen("Score: "),10,200);
		drawText(buf,strlen(buf), 200, 200);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glViewport(WIDTH/2+200, HEIGHT/2, 300, HEIGHT/2);
	glEnable (GL_TEXTURE_GEN_S);
  	glEnable (GL_TEXTURE_GEN_T);
  	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture (GL_TEXTURE_2D, textures[0]);
	glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv (GL_S, GL_EYE_PLANE, plane_xy);
	glTexGenfv (GL_T, GL_EYE_PLANE, plane_yz);
	glPushMatrix ();
		// glTranslatef (-1, -1, 0);
		Teapot();
	glPopMatrix ();
	glFlush();
	glutSwapBuffers();
}

void reshape (int w, int h) {
	// glViewport (0, 0, 1000, h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glViewport (0, 0, w, h);
	glMatrixMode (GL_MODELVIEW);
	glutPostRedisplay();
	// glLoadIdentity ();
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
	if(type==1)
	{
		// printf("type==%d\n",type );
		int temp_x=rand()%7;
		int temp_y=rand()%7;
		x[0]=x[1]=temp_x;
		x[2]=x[3]=temp_x+1;
		y[0]=y[2]=temp_y;
		y[1]=y[3]=temp_y+1;
		z[0]=z[1]=z[2]=z[3]=8;

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
		temp_block=create_block(squareshape, 1);
		current_block=set_block(global_type_block, color_block,temp_block);
		tetris_board_place_block(tetris_board,current_block, CELL(x[i], y[i],z[i]),z[i]);
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
// tetris_board_place_block_at_boardvalue(tetris_board, current_block, CELL(x_temp, y_temp,current_z),temp);
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
		type= rand()%4 +1;
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

void rotate()
{

}



void timer(int extra) {
	glutPostRedisplay();
	while(!executed);
	while(time_status>=speed)
	{
		time_status=0;
		update_game();
	}
	if(time_count%250==0)
	{
		speed--;
		printf("speed increased\n");
	}
	if(speed< 30)
	{
		speed=30;
	}
	time_count++;
	time_status++;
	glutTimerFunc(1, timer, 0);
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
void keypressSpecial(int key, int x, int y){
	if (key == GLUT_KEY_UP) {
		loadSound("./wav/tick.wav"); playSound();
		// if(!collision())
		if(allow_movement)
		move_block_up();
	}
	if (key== GLUT_KEY_DOWN){
		loadSound("./wav/tick.wav"); playSound();
		if(allow_movement)
		move_block_down();
	}
	if (key== GLUT_KEY_LEFT){
		loadSound("./wav/tick.wav"); playSound();
		if(allow_movement)
		move_block_left();
	}
	if (key== GLUT_KEY_RIGHT){
		loadSound("./wav/tick.wav"); playSound();
		if(allow_movement)
		move_block_right();
	}

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
	// First loading texture and doing stuff
	unsigned char texture[NUM_TEXTURES][3*64*64];
	unsigned int i;
	static texture_info_t textures_info[] = {
		{"marble.jpg", GL_RGB, 64},
		{0, 0, 0}
	};

	glutInit(&argc, argv);
	alutInit (&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize (WIDTH, HEIGHT);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("3D-Tetris");
	// glEnable (GL_CULL_FACE);
 //  	glCullFace (GL_FRONT);
  	glEnable (GL_BLEND);
  	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  	// glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
  	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  	glEnable(GL_TEXTURE_2D);

  	/*Texture Loading */
  	glGenTextures(NUM_TEXTURES, textures);
  	for(i = 0; textures_info[i].name != 0 ; i++) {
  		if(load_texture(textures_info[i].name,
  			texture[i],
  			textures_info[i].format,
  			textures_info[i].size) !=0)
			return 1;
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		// gluBuild2DMipMaps(GL_TEXTURE_2D,textures_info[i].format,
		// textures_info[i].size, textures_info[i].size,
		// 	 textures_info[i].format,
		// 	 GL_UNSIGNED_BYTE,  texture[i]);

		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  	}

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


