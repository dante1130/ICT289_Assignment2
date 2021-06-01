#include <GL/freeglut.h>
#include <stdbool.h>
#include "Camera.h"
#include "OffLoader.h"
#include "GameObject.h"
#include "Player.h"
#include "VectorGameObject.h"

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

// Used for lighting
GLfloat light_position[] = { 0, 1, 0.1, 0.0 };

// Declaration of objects
Player player;

GameObject world;
GameObject bottle;
GameObject bench;
GameObject vase;
GameObject gun;

VectorGameObject vectorObjects;

void objectsInit()
{
    //Initialize player
    playerInit(&player);

     // Read 3D objects via off files
    player.weapon = readOFFFile("Objects/gun2.off");
    world.obj3D = readOFFFile("Objects/world.off");
    bottle.obj3D = readOFFFile("Objects/bottle.off");
    bench.obj3D = readOFFFile("Objects/bench.off");
    vase.obj3D = readOFFFile("Objects/vase.off");

    // Set color
    setColor(&world.obj3D, 1.0, 1.0, 1.0);
    setColor(&bottle.obj3D, 0.0, 0.0, 1.0);
    setColor(&bench.obj3D, 0.8, 0.65, 0.45);
    setColor(&vase.obj3D, 0.0, 1.0, 0.0);

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

    vectorInit(&vectorObjects);

    vectorPush(&vectorObjects, &world);
    vectorPush(&vectorObjects, &bottle);
    vectorPush(&vectorObjects, &bench);
    vectorPush(&vectorObjects, &vase);
    // vectorPush(&vectorObjects, &gun);
}

void init()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

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

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Initialise objects
    objectsInit();
}

void reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION); // switch matrix mode to projection
    glLoadIdentity();

    glViewport(0, 0, w, h);

    //Viewing volume
    GLdouble fov = 60;
    GLdouble aspect = w / (GLfloat) h;
    GLdouble nearVal = 0.1;
    GLdouble farVal = 1000;
    gluPerspective(fov, aspect, nearVal, farVal);

    elapsedTime = glutGet(GLUT_ELAPSED_TIME);
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

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    vectorDrawObj(&vectorObjects);
    vectorDrawObj(&player.bullets);

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

    case 27: // ESC key
        exit(0);
        break;
    }

//    if (!(isBoxCollidePoint(world.bBox, player.camera.eye)))
//    {
//        player.camera.eye = prevPos;
//    }

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
        shoot(&player, 10);
    }
}

void animate()
{
    glutTimerFunc(TIMERSEC, animate, 0);

    float newElapsedTime = glutGet(GLUT_ELAPSED_TIME);
    delta = (newElapsedTime - elapsedTime) / 1000;
    elapsedTime = newElapsedTime;


    for (int i = 0; i < player.bullets.size; ++i)
    {
        updateGameObj(&player.bullets.array[i], delta);

        if (player.bullets.array[i].physics.position.y <= 0.1)
        {
            player.bullets.array[i].physics.position.y = 0.1;
            invertVelocityY(&player.bullets.array[i].physics);
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
    glutReshapeFunc(reshape);
    glutDisplayFunc(display); // callback that is invoked when window is displayed
    glutKeyboardFunc(keys); // interaction with keyboard keys
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(mouseMove); // interaction with moving the mouse
    glutMotionFunc(mouseMove); // interaction with moving the mouse (onClicked)

    glutTimerFunc(TIMERSEC, animate, 0);
    glutMainLoop(); // enter event loop

    // Free objects from memory
    vectorDelete(&vectorObjects);
    vectorDelete(&player.bullets);
    freeObject3D(&player.weapon);
    freeObject3D(&world.obj3D);
    freeObject3D(&bottle.obj3D);
    freeObject3D(&bench.obj3D);
    freeObject3D(&vase.obj3D);

    return 0;
}
