#include <GL/freeglut.h>
#include <stdbool.h>
#include "Camera.h"
#include "OffLoader.h"
#include "GameObject.h"

#define M_PI 3.14159265358979323846

// Define window size
const int windowWidth = 1920;
const int windowHeight = 1080;

// Used for keyboard movement
const float cameraSpeed = 0.1;

// Used for mouse movement
bool firstMouse = 1;

float prevX = 0;
float prevY = 0;

// Declaration of objects
Camera camera;

GameObject world;
GameObject bottle;
GameObject bench;
GameObject vase;
GameObject gun;

void init()
{
    // set attributes
    glClearColor(0.0, 0.0, 0.0, 0.0); // black background
    glColor3f(0.0, 0.0, 1.0); // draw with color
    glLineWidth(1.0);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glMatrixMode(GL_PROJECTION); // switch matrix mode to projection
    glLoadIdentity();

    //Viewing volume
    GLdouble fov = 60;
    GLdouble aspect = windowWidth / (GLfloat) windowHeight;
    GLdouble nearVal = 0.1;
    GLdouble farVal = 1000;
    gluPerspective(fov, aspect, nearVal, farVal);

    //Initialize camera
    ResetCamera(&camera);

    // Read 3D objects via off files
    world.obj3D = readOFFFile("Objects/world.off");
    bottle.obj3D = readOFFFile("Objects/bottle.off");
    bench.obj3D = readOFFFile("Objects/bench.off");
    vase.obj3D = readOFFFile("Objects/vase.off");
    gun.obj3D = readOFFFile("Objects/gun2.off");

    //normalizeObject3D(&bottle.obj3D);

    //Initialize collision
    getBoundingBoxExtents(world.obj3D, &world.bBox.minExtent, &world.bBox.maxExtent);
    getBoundingBoxExtents(bottle.obj3D, &bottle.bBox.minExtent, &bottle.bBox.maxExtent);
    getBoundingBoxExtents(bench.obj3D, &bench.bBox.minExtent, &bench.bBox.maxExtent);
    getBoundingBoxExtents(vase.obj3D, &vase.bBox.minExtent, &vase.bBox.maxExtent);
}

void display()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // clear the window to background color specified by glClearColor()

    glMatrixMode(GL_MODELVIEW); // switch matrix mode back to model view
    glLoadIdentity();

    gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
              camera.eye.x + camera.center.x, camera.eye.y + camera.center.y, camera.eye.z + camera.center.z,
              camera.up.x, camera.up.y, camera.up.z);

    // The world
    drawWorld(world.obj3D);

    // Gun
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    glTranslatef(camera.eye.x + camera.center.x, camera.eye.y + camera.center.y, camera.eye.z + camera.center.z);
    glRotatef(90, 0, 1, 0);
    drawObject3D(gun.obj3D);
    glPopMatrix();

    // Bottle
    glColor3f(0.0, 0.0, 1.0);
    drawObject3D(bottle.obj3D);

    // test draw bounding box
    glColor3f(1.0, 0.0, 0.0);
    drawBoundingBox(bottle.bBox);

    glutSwapBuffers(); // swap buffer
}

void keys(unsigned char key, int x, int y)
{
    Vector3 prevPos = camera.eye;

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

    if (!(isBoxCollidePoint(world.bBox, camera.eye)))
    {
        camera.eye = prevPos;
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
    else if (camera.pitch < -89.0f)
    {
        camera.pitch = -89.0f;
    }

    camera.center.x = sin(degreesToRadians(camera.yaw)) * cos(degreesToRadians(camera.pitch));
    camera.center.y = sin(degreesToRadians(camera.pitch));
    camera.center.z = -cos(degreesToRadians(camera.yaw)) * cos(degreesToRadians(camera.pitch));

    camera.center = normalize(camera.center);

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
    freeObject3D(world.obj3D);
    freeObject3D(bottle.obj3D);
    freeObject3D(bench.obj3D);
    freeObject3D(vase.obj3D);
    freeObject3D(gun.obj3D);

    return 0;
}
