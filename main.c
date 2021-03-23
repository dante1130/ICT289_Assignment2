#include <GL/freeglut.h>

void myInit()
{
    // set attributes
    glClearColor(0.0, 0.0, 0.0, 0.0); // white background
    glColor3f(0.0, 0.0, 1.0); // draw red
    glLineWidth(1.0); // draw with 5 pixel wide

    glMatrixMode(GL_PROJECTION); // switch matrix mode to projection
    glLoadIdentity(); // Load an identity matrix as the projection matrix

    //Viewing volume
    GLdouble fov = 30;
    GLdouble aspect = 1;
    GLdouble nearVal = 0.1;
    GLdouble farVal = 100;
    gluPerspective(fov, aspect, nearVal, farVal);

    glMatrixMode(GL_MODELVIEW); // switch matrix mode back to model view

    glLoadIdentity();

    gluLookAt(2, 2, 5,
              0, 0, 0,
              0, 1, 0);
}

void display()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // clear the window to background color specified by glClearColor()


    glFlush(); // flush buffer
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initialization of GLUT
    glutInitWindowSize(500, 500); // 500 x 500 pixels window
    glutInitWindowPosition(0, 0); // place at top left of the window display
    glutCreateWindow("Window"); // Names the window title
    myInit(); // set attributes
    glutDisplayFunc(display); // callback that is invoked when window is displayed
    glutMainLoop(); // enter event loop

    return 0;
}
