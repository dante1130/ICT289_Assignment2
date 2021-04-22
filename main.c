#include <GL/freeglut.h>
#include <stdbool.h>
#include "Camera.h"
#include "OffLoader.h"
#include "GameObject.h"
#include "Player.h"

#define M_PI 3.14159265358979323846

const float TIMERSEC = 1000.0 / 60.0;

float elapsedTime = 0;
float delta = 0;

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
Player player;

GameObject world;
GameObject bottle;
GameObject bench;
GameObject vase;
GameObject gun;

// Turn on gravity
bool activateGrav = 0;

void init()
{
    // set attributes
    glClearColor(0.0, 0.0, 0.0, 0.0); // black background
    glColor3f(0.0, 0.0, 1.0); // draw with color
    glLineWidth(1.0);

    // Enable face culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // Enable depth
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

    // Read 3D objects via off files
    world.obj3D = readOFFFile("Objects/world.off");
    bottle.obj3D = readOFFFile("Objects/bottle.off");
    bench.obj3D = readOFFFile("Objects/bench.off");
    vase.obj3D = readOFFFile("Objects/vase.off");
    player.weapon = readOFFFile("Objects/gun2.off");
    player.bullet.obj3D = readOFFFile("Objects/ball.off");

    //Initialize player
    playerInit(&player);

    // Initialize collision
    getBoundingBoxExtents(world.obj3D, &world.bBox.minExtent, &world.bBox.maxExtent);
    getBoundingBoxExtents(bottle.obj3D, &bottle.bBox.minExtent, &bottle.bBox.maxExtent);
    getBoundingBoxExtents(bench.obj3D, &bench.bBox.minExtent, &bench.bBox.maxExtent);
    getBoundingBoxExtents(vase.obj3D, &vase.bBox.minExtent, &vase.bBox.maxExtent);

    // Initialize physics
    SetPhysics(&world.physics, 100000);
    SetPhysics(&bottle.physics, 1);
    SetPhysics(&bench.physics, 100);
    SetPhysics(&vase.physics, 5);

    // Translate objects
    translateGameObj(&bench, 0, bench.bBox.maxExtent.y / 2, -9);
    translateGameObj(&bottle, 0, (bottle.bBox.maxExtent.y / 2) + bench.bBox.maxExtent.y, bench.physics.position.z);
    translateGameObj(&vase, 0.25, (vase.bBox.maxExtent.y / 2) + bench.bBox.maxExtent.y, bench.physics.position.z);
}

void display()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // clear the window to background color specified by glClearColor()

    glMatrixMode(GL_MODELVIEW); // switch matrix mode back to model view
    glLoadIdentity();

    gluLookAt(player.camera.eye.x, player.camera.eye.y, player.camera.eye.z,
              player.camera.eye.x + player.camera.center.x,
              player.camera.eye.y + player.camera.center.y,
              player.camera.eye.z + player.camera.center.z,
              player.camera.up.x, player.camera.up.y, player.camera.up.z);

    // The world
    glPushMatrix();
    glTranslatef(world.physics.position.x, world.physics.position.y, world.physics.position.z);
    drawWorld(world.obj3D);
    glPopMatrix();

    // Gun
    //drawGun(&player);

    // Bottle
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslatef(bottle.physics.position.x, bottle.physics.position.y, bottle.physics.position.z);
    drawObject3D(bottle.obj3D);
    glPopMatrix();

    // Bench
    glColor3f(0.8, 0.65, 0.45);
    glPushMatrix();
    glTranslatef(bench.physics.position.x, bench.physics.position.y, bench.physics.position.z);
    drawObject3D(bench.obj3D);
    glPopMatrix();

    // Vase
    glColor3f(0.1, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(vase.physics.position.x, vase.physics.position.y, vase.physics.position.z);
    drawObject3D(vase.obj3D);
    glPopMatrix();

    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(player.bullet.physics.position.x, player.bullet.physics.position.y, player.bullet.physics.position.z);
    drawObject3D(player.bullet.obj3D);
    glPopMatrix();

    glutSwapBuffers(); // swap buffer
}

void keys(unsigned char key, int x, int y)
{
    Vector3 prevPos = player.camera.eye;

    switch (key)
    {
    case 'w':
        MoveForward(&player.camera, cameraSpeed);
        break;

    case 'a':
        MoveLeft(&player.camera, cameraSpeed);
        break;

    case 's':
        MoveBackward(&player.camera, cameraSpeed);
        break;

    case 'd':
        MoveRight(&player.camera, cameraSpeed);
        break;

    case 'g':
        activateGrav = 1;
        printf("grva = %d", activateGrav);
        break;

    case 27: // ESC key
        exit(0);
        break;
    }

    if (!(isBoxCollidePoint(world.bBox, player.camera.eye)))
    {
        player.camera.eye = prevPos;
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

    player.camera.yaw += xOffset;
    player.camera.pitch += yOffset;

    //
    if(player.camera.pitch > 89.0f)
    {
        player.camera.pitch = 89.0f;
    }
    else if (player.camera.pitch < -89.0f)
    {
        player.camera.pitch = -89.0f;
    }

    player.camera.center.x = sin(degreesToRadians(player.camera.yaw)) * cos(degreesToRadians(player.camera.pitch));
    player.camera.center.y = sin(degreesToRadians(player.camera.pitch));
    player.camera.center.z = -cos(degreesToRadians(player.camera.yaw)) * cos(degreesToRadians(player.camera.pitch));

    player.camera.center = normalize(player.camera.center);

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        shoot(&player);
    }
}

void animate()
{
    glutTimerFunc(TIMERSEC, animate, 0);

    float newElapsedTime = glutGet(GLUT_ELAPSED_TIME);
    delta = (newElapsedTime - elapsedTime) / TIMERSEC;
    elapsedTime = newElapsedTime;

    updateGameObj(&player.bullet, delta);

    if (player.bullet.physics.position.y <= 0.1)
    {
        player.bullet.physics.position.y = 0.1;
        invertVelocityY(&player.bullet.physics);
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
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(mouseMove); // interaction with moving the mouse
    glutMotionFunc(mouseMove); // interaction with moving the mouse (onClicked)

    glutTimerFunc(TIMERSEC, animate, 0);
    glutMainLoop(); // enter event loop

    // Free objects from memory
    freeObject3D(world.obj3D);
    freeObject3D(bottle.obj3D);
    freeObject3D(bench.obj3D);
    freeObject3D(vase.obj3D);
    freeObject3D(player.weapon);
    freeObject3D(player.bullet.obj3D);

    return 0;
}
