#include "objloader.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>

#ifdef __WIN32__
#include <windows.h>
#endif

#include "GL/glut.h"  //glut has all ogl relevant .h files included 

int screen_width=800;
int screen_height=600;

//angle of rotation
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle=0.0;

float cRadius = 10.0f; // our radius distance from our character

float lastx, lasty;

object_type *objarray[2];  //objects container for our world. Used throughout so global

//Lights settings
GLfloat light_ambient[]= { 0.1f, 0.1f, 0.1f, 0.1f };
GLfloat light_diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_specular[]= { 0.5f, 0.5f, 0.5f, 0.0f };
GLfloat light_position1[]= { 100.0f, 0.0f, -10.0f, 1.0f };
GLfloat light_position2[]= { -100.0f, 30.0f, -10.0f, 1.0f };

//Materials settings
GLfloat mat_ambient[]= { 0.5f, 0.5f, 0.3f, 0.0f };
GLfloat mat_diffuse[]= { 0.5f, 0.5f, 0.0f, 0.0f };
GLfloat mat_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat mat_shininess[]= { 1.0f };


/************************************
 *
 * SUBROUTINE init(void)
 *
 * Used to initialize OpenGL and to setup our world
 *
************************************/

 void init(void)
 {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Clear background color to black

    // Viewport transformation
    glViewport(0,0,screen_width,screen_height);  

    // Projection transformation
    glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations 
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,5.0f,10000.0f);     


//Lights initialization and activation
    glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light_specular);
    glLightfv (GL_LIGHT1, GL_POSITION, light_position1);    
    glLightfv (GL_LIGHT1, GL_POSITION, light_position2);    
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);

    //Materials initialization and activation
    glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_specular);
    glMaterialfv (GL_FRONT, GL_POSITION, mat_shininess);    

//Other initializations
    glShadeModel(GL_SMOOTH); // Type of shading for the polygons
    glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Texture mapping perspective correction
    glEnable(GL_TEXTURE_2D); // Texture mapping ON
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
    glEnable(GL_CULL_FACE); // Enable the back face culling
    glEnable(GL_DEPTH_TEST); // Enable the depth test 

    glTranslatef(0.0f, 0.0f, -cRadius);
    glRotatef(xrot,1.0,0.0,0.0);

angle++; //increase the angle

for (int i=0;i<2;i++)
{
    printf("*************\n");
    objarray[i] = new (object_type);
    char* path1 = "game_models/tshape.obj";
    //printf("%s",path);
    objarray[i]->objloader(path1);
    objarray[i]->objdatadisplay();      
}

}


/**********************************************************
 *
 * SUBROUTINE resize(int p_width, int p_height)
 *
 * This routine must be called everytime we resize our window.
 *
 * Input parameters: p_width = width in pixels of our viewport
 *                   p_height = height in pixels of our viewport
 * 
 *********************************************************/

 void resize (int p_width, int p_height)
 {
    if (screen_width==0 && screen_height==0) exit(0);
    screen_width=p_width; // We obtain the new screen width values and store it
    screen_height=p_height; // Height value

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We clear both the color and the depth buffer so to draw the next frame
    glViewport(0,0,screen_width,screen_height); // Viewport transformation

    glMatrixMode(GL_PROJECTION); // Projection transformation
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,5.0f,10000.0f);

    glutPostRedisplay (); // This command redraw the scene (it calls the same routine of glutDisplayFunc)
}

/**********************************************************
 *
 * SUBROUTINE keyboard(void)
 *
 * Subroutine to handle keyboard input
 * 
 *********************************************************/


 void keyboard (unsigned char key, int x, int y) {
    if (key=='q')
    {
        xrot += 1;
        if (xrot >360) xrot -= 360;
    }

    if (key=='z')
    {
        xrot -= 1;

        if (xrot < -360) xrot += 360;
    }

    if (key=='w')
    {
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f); 
        xpos += float(sin(yrotrad));
        zpos -= float(cos(yrotrad));
        ypos -= float(sin(xrotrad));
    }

    if (key=='s')
    {
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f); 
        xpos -= float(sin(yrotrad));
        zpos += float(cos(yrotrad));
        ypos += float(sin(xrotrad));
    }

    if (key=='d')
    {
        float yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xpos += float(cos(yrotrad)) * 0.2;
        zpos += float(sin(yrotrad)) * 0.2;
    }

    if (key=='a')
    {
        float yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xpos -= float(cos(yrotrad)) * 0.2;
        zpos -= float(sin(yrotrad)) * 0.2;
    }

    if (key==27)
    {
        exit(0);
    }
}

/**********************************************************
 *
 * SUBROUTINE mouseMovement(void)
 *
 * Subroutine to handle mouse input
 * 
 *********************************************************/

 void mouseMovement(int x, int y) {
    int diffx=x-lastx; //check the difference between the current x and the last x position
    int diffy=y-lasty; //check the difference between the current y and the last y position
    lastx=x; //set lastx to the current x position
    lasty=y; //set lasty to the current y position
    xrot += (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
    yrot += (float) diffx;    //set the xrot to yrot with the addition of the difference in the x position
}


/**********************************************************
 *
 * SUBROUTINE display(void)
 *
 * This is our main rendering subroutine, called each frame
 * 
 *********************************************************/

 void display(void)
 {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue
    glMatrixMode(GL_MODELVIEW); // Modeling transformation
    glPushMatrix();
    glLoadIdentity(); // Initialize the model matrix as identity

    glTranslatef(0.0f, 0.0f, -cRadius); // We move the object forward (the model matrix is multiplied by the translation matrix)
    glRotatef(xrot,1.0,0.0,0.0); // Rotations of the object (the model matrix is multiplied by the rotation matrices)

    glRotatef(yrot,0.0,1.0,0.0);

    glTranslated(-xpos,0.0f,-zpos); //translate the screen to the position of our camera


if (objarray[0]->id_texture!=-1) 
{
    glBindTexture(GL_TEXTURE_2D, objarray[0]->id_texture); // We set the active texture 
    glEnable(GL_TEXTURE_2D); // Texture mapping ON
    //printf("Txt map ON");
}
else
    glDisable(GL_TEXTURE_2D); // Texture mapping OFF


    objarray[0]->render();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5.0,0.0,-20.0);
    glFlush(); // This force the execution of OpenGL commands
    glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer
}



/**********************************************************
 *
 * The main routine
 * 
 *********************************************************/


 int main(int argc, char **argv)
 {
    // We use the GLUT utility to initialize the window, to handle the input and to interact with the windows system
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Demo 1: To exit press ESC");    
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc (resize);

    glutPassiveMotionFunc(mouseMovement); //check for mouse movement
    glutKeyboardFunc (keyboard); 

    init();
    glutMainLoop();

return(0);    
}