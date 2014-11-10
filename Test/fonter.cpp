#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "GL/glu.h"
//glm not required
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
#include <string>

int win_width = 500, win_height = 500;

void renderScene(void) {

    static float dis=0, ddis=0, elev=0, delev=0, azim=0, dazim=0;

    azim += 0.5f;
    if (azim >= 360.0f){
        azim -= 360.0f;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -(dis + ddis));
    glRotated(elev + delev, 1.0, 0.0, 0.0);
    glRotated(azim + dazim, 0.0, 1.0, 0.0);
    glScalef(2.0f,2.0f,2.0f);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    //I like to use glm because glu is deprecated
    //glm::mat4 orth= glm::ortho(0.0f, (float)win_width, 0.0f, (float)win_height);
    //glMultMatrixf(&(orth[0][0]));
    gluOrtho2D(0.0, win_width, 0.0, win_height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f);//needs to be called before RasterPos
    glRasterPos2i(10, 10);
    std::string s = "Some text";
    void * font = GLUT_BITMAP_9_BY_15;

    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        //this does nothing, color is fixed for Bitmaps when calling glRasterPos
        //glColor3f(1.0, 0.0, 1.0); 
        glutBitmapCharacter(font, c);
    }
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);

    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char **argv) {

    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("GLUT Test");

    // register callbacks
    glutDisplayFunc(renderScene);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}