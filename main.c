#include <GL/freeglut.h>
#include "Camera.h"

const int windowWidth = 1280;
const int windowHeight = 720;

Camera camera;

const float cameraSpeed = 0.1;

void init()
{
    // set attributes
    glClearColor(0.0, 0.0, 0.0, 0.0); // black background
    glColor3f(0.0, 0.0, 1.0); // draw red
    glLineWidth(1.0); // draw with 5 pixel wide

    glMatrixMode(GL_PROJECTION); // switch matrix mode to projection
    glLoadIdentity(); // Load an identity matrix as the projection matrix

    //Viewing volume
    GLdouble fov = 60;
    GLdouble aspect = windowWidth / (GLfloat) windowHeight;
    GLdouble nearVal = 0.1;
    GLdouble farVal = 1000;
    gluPerspective(fov, aspect, nearVal, farVal);

    //Initialize camera
    camera = CreateCamera();

    glMatrixMode(GL_MODELVIEW); // switch matrix mode back to model view
}

void display()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // clear the window to background color specified by glClearColor()

    glLoadIdentity();
    gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
              camera.center.x, camera.center.y, camera.center.z,
              camera.up.x, camera.up.y, camera.up.z);

    // Sample object to test
    glutWireTeapot(1.0);

    glutSwapBuffers(); // swap buffer
}

void keys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        MoveForward(&camera, cameraSpeed);
        break;

    case 'a':
        MoveLeft(&camera, cameraSpeed);
        break;

    case 's':
        MoveBackward(&camera, cameraSpeed);
        break;

    case 'd':
        MoveRight(&camera, cameraSpeed);
        break;
    }

    // Redisplay the window content
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initialization of GLUT
    glutInitWindowSize(windowWidth, windowHeight); // 500 x 500 pixels window
    glutInitWindowPosition(0, 0); // place at top left of the window display
    glutCreateWindow("Shooting range"); // Names the window title

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    init(); // initialize attributes
    glutDisplayFunc(display); // callback that is invoked when window is displayed
    glutKeyboardFunc(keys); // interaction with keyboard

    glutMainLoop(); // enter event loop

    return 0;
}
