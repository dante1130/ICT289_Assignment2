#include <GL/freeglut.h>
#include <stdbool.h>
#include "Camera.h"
#include "OffLoader.h"
#include "Object3D.h"

#define M_PI 3.14159265358979323846

// Define window size
const int windowWidth = 1920;
const int windowHeight = 1080;

// Used for keyboard movement
const float cameraSpeed = 0.1;

// Used for mouse movement
bool firstMouse = 1;

float prevX;
float prevY;

// Declaration of objects
Camera camera;
Object3D gun;

void init()
{
    // set attributes
    glClearColor(0.0, 0.0, 0.0, 0.0); // black background
    glColor3f(0.0, 0.0, 1.0); // draw with color
    glLineWidth(1.0);

    glMatrixMode(GL_PROJECTION); // switch matrix mode to projection
    glLoadIdentity(); // Load an identity matrix as the projection matrix

    //Viewing volume
    GLdouble fov = 60;
    GLdouble aspect = windowWidth / (GLfloat) windowHeight;
    GLdouble nearVal = 0.1;
    GLdouble farVal = 1000;
    gluPerspective(fov, aspect, nearVal, farVal);

    // Read 3D objects via off files
    gun = readOFFFile("Objects/gun2.off");

    //Initialize camera
    camera = CreateCamera();

    glMatrixMode(GL_MODELVIEW); // switch matrix mode back to model view
}

void display()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // clear the window to background color specified by glClearColor()

    glLoadIdentity();
    gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
              camera.eye.x + camera.center.x, camera.center.y, camera.eye.z + camera.center.z,
              camera.up.x, camera.up.y, camera.up.z);


    // Sample object to test
    //glutWireTeapot(1.0);

    drawObject3D(gun);

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

    case 27: // ESC key
        exit(0);
        break;
    }

    // Redisplay the window content
    glutPostRedisplay();
}

float degreesToRadians(float degrees)
{
    return degrees * M_PI / 180;
}

void mouseMove(int x, int y)
{
    if (firstMouse)
    {
        prevX = x;
        prevY = y;
        firstMouse = 0;
    }

    float xOffset = x - prevX;
    float yOffset = prevY - y;
    prevX = x;
    prevY = y;

    float sensitivity = 1;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    camera.yaw += xOffset;
    camera.pitch += yOffset;

    //
    if(camera.pitch > 89.0f)
    {
        camera.pitch = 89.0f;
    }

    if (camera.pitch < -89.0f)
    {
        camera.pitch = -89.0f;
    }

    camera.center.x = sin(degreesToRadians(camera.yaw)) * cos(degreesToRadians(camera.pitch));
    camera.center.y = sin(degreesToRadians(camera.pitch));
    camera.center.z = -cos(degreesToRadians(camera.yaw)) * cos(degreesToRadians(camera.pitch));

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initialization of GLUT
    glutInitWindowSize(windowWidth, windowHeight); // 1920 x 1080 pixels window
    glutInitWindowPosition(0, 0); // place at top left of the window display
    glutCreateWindow("Shooting range"); // Names the window title
    glutSetCursor(GLUT_CURSOR_NONE); // Removes the cursor
    glutFullScreen(); // Turns window to fullscreen

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    init(); // initialize attributes
    glutDisplayFunc(display); // callback that is invoked when window is displayed
    glutKeyboardFunc(keys); // interaction with keyboard keys
    glutPassiveMotionFunc(mouseMove); // interaction with moving the mouse
    glutMotionFunc(mouseMove); // interaction with moving the mouse (onClicked)

    glutMainLoop(); // enter event loop

    // Free objects from memory
    freeObject3D(gun);

    return 0;
}
