#include <GL/freeglut.h>
#include <stdbool.h>
#include "Camera.h"
#include "OffLoader.h"
#include "GameObject.h"

#define M_PI 3.14159265358979323846
#define TIMERSEC 33

// Define window size
const int windowWidth = 1280;
const int windowHeight = 720;

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

GameObject ballA;
GameObject ballB;

// Turn on gravity
bool activateGrav = 0;

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
    ballA.obj3D = readOFFFile("Objects/ball.off");
    ballB.obj3D = readOFFFile("Objects/ball.off");

    // Normalize objects as needed

    //Initialize collision
    getBoundingBoxExtents(world.obj3D, &world.bBox.minExtent, &world.bBox.maxExtent);
    getBoundingBoxExtents(bottle.obj3D, &bottle.bBox.minExtent, &bottle.bBox.maxExtent);
    getBoundingBoxExtents(bench.obj3D, &bench.bBox.minExtent, &bench.bBox.maxExtent);
    getBoundingBoxExtents(vase.obj3D, &vase.bBox.minExtent, &vase.bBox.maxExtent);
    getBoundingSphere(ballA.obj3D, &ballA.bSphere.center, &ballA.bSphere.radius);
    getBoundingSphere(ballB.obj3D, &ballB.bSphere.center, &ballB.bSphere.radius);

    SetPhysics(&ballA.physics, 1);
    ballA.physics.velocity.x = 0.00001;
    SetPhysics(&ballB.physics, 1);
    ballB.physics.velocity.x = -0.00001;

    // Translate objects
    translateGameObj(&ballB, 2, 0, 0);
}

void display()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // clear the window to background color specified by glClearColor()

    glMatrixMode(GL_MODELVIEW); // switch matrix mode back to model view
    glLoadIdentity();

    gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
              camera.eye.x + camera.center.x, camera.eye.y + camera.center.y, camera.eye.z + camera.center.z,
              camera.up.x, camera.up.y, camera.up.z);

     // Sample object to test
    glPushMatrix();
    glTranslatef(ballA.physics.position.x, ballA.physics.position.y, ballA.physics.position.z);
    glColor3f(0.0, 0.0, 1.0);
    drawObject3D(ballA.obj3D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(ballB.physics.position.x, ballB.physics.position.y, ballB.physics.position.z);
    glColor3f(0.0, 1.0, 1.0);
    drawObject3D(ballB.obj3D);
    glPopMatrix();



    /*
    // The world
    glPushMatrix();
    glTranslatef(0, 0, 0);
    drawWorld(world.obj3D);
    glPopMatrix();

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
    drawBoundingBox(ballA.bBox);
    drawBoundingBox(ballB.bBox);
    */

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

    case 'g':
        activateGrav = 1;
        printf("grva = %d", activateGrav);
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

void animate()
{
    glutTimerFunc(TIMERSEC, animate, 0);

    if (activateGrav == 1)
    {
        updateGameObj(&ballA, TIMERSEC);
        updateGameObj(&ballB, TIMERSEC);

        if (isSphereCollide(ballA.bSphere, ballB.bSphere))
        {
            NewProjection(&ballA.physics, &ballB.physics);
        }

        //Bounce off floor
        if(ballA.physics.position.y < -1)
        {
            invertVelocityY(&ballA.physics);
            ballA.physics.velocity.x = ballA.physics.velocity.x * 1;
            ballA.physics.velocity.z = ballA.physics.velocity.z * 1;
        }

        //Bounce off floor
        if(ballB.physics.position.y < -1)
        {
            invertVelocityY(&ballB.physics);
            ballB.physics.velocity.x = ballB.physics.velocity.x * 1;
            ballB.physics.velocity.z = ballB.physics.velocity.z * 1;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initialization of GLUT
    glutInitWindowSize(windowWidth, windowHeight); // 1920 x 1080 pixels window
    glutInitWindowPosition(0, 0); // place at top left of the window display
    glutCreateWindow("Shooting range"); // Names the window title
    glutSetCursor(GLUT_CURSOR_NONE); // Removes the cursor
    //glutFullScreen(); // Turns window to fullscreen

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    init(); // initialize attributes
    glutDisplayFunc(display); // callback that is invoked when window is displayed
    glutKeyboardFunc(keys); // interaction with keyboard keys
    glutPassiveMotionFunc(mouseMove); // interaction with moving the mouse
    glutMotionFunc(mouseMove); // interaction with moving the mouse (onClicked)

    glutIdleFunc(animate);
    glutMainLoop(); // enter event loop

    // Free objects from memory
    freeObject3D(world.obj3D);
    freeObject3D(bottle.obj3D);
    freeObject3D(bench.obj3D);
    freeObject3D(vase.obj3D);
    freeObject3D(gun.obj3D);
    freeObject3D(ballA.obj3D);
    freeObject3D(ballB.obj3D);

    return 0;
}
