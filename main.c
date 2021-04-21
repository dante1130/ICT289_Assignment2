#include <GL/freeglut.h>
#include <stdbool.h>
#include "Camera.h"
#include "OffLoader.h"
#include "Physics3D.h"
#include "GameObject.h"

#define M_PI 3.14159265358979323846
#define TIMERSEC 33

// Define window size
const int windowWidth = 500;
const int windowHeight = 500;

// Used for keyboard movement
const float cameraSpeed = 0.1;

// Used for mouse movement
bool firstMouse = 1;

float prevX = 0;
float prevY = 0;

// Declaration of objects
Camera camera;
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

    glMatrixMode(GL_PROJECTION); // switch matrix mode to projection
    glLoadIdentity();

    //Viewing volume
    GLdouble fov = 60;
    GLdouble aspect = windowWidth / (GLfloat) windowHeight;
    GLdouble nearVal = 0.1;
    GLdouble farVal = 1000;
    gluPerspective(fov, aspect, nearVal, farVal);

    // Read 3D objects via off files
    ballA.obj3D = readOFFFile("Objects/ball.off");
    ballB.obj3D = readOFFFile("Objects/ball.off");
    //normalizeObject3D(&bottle.obj3D);

    getBoundingBoxExtents(ballA.obj3D, &ballA.bBox.minExtent, &ballA.bBox.maxExtent);
    getBoundingBoxExtents(ballB.obj3D, &ballB.bBox.minExtent, &ballB.bBox.maxExtent);

    //Initialize camera
    ResetCamera(&camera);
}

void drawGrass()
{
    glColor3f(0,1.0,0);
    glBegin(GL_POLYGON);
        glVertex3f(5,-1,5);
        glVertex3f(5, -1,-5);
        glVertex3f(-5,-1,-5);
        glVertex3f(-5,-1,5);
    glEnd();
}

void display()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // clear the window to background color specified by glClearColor()

    glMatrixMode(GL_MODELVIEW); // switch matrix mode back to model view
    glLoadIdentity();

    gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
              camera.eye.x + camera.center.x, camera.eye.y + camera.center.y, camera.eye.z + camera.center.z,
              camera.up.x, camera.up.y, camera.up.z);

    drawGrass();

    // Sample object to test
    glPushMatrix();
    glTranslatef(ballA.physics.position.x, ballA.physics.position.y, ballA.physics.position.z);
    glColor3f(0.0, 0.0, 1.0);
    drawObject3D(ballA.obj3D);
    glPopMatrix();
    // test draw bounding box
    glColor3f(1.0, 0.0, 0.0);
    drawBoundingBox(ballA.bBox);

    glTranslatef(2,0,0);
    glTranslatef(ballB.physics.position.x, ballB.physics.position.y, ballB.physics.position.z);
    glColor3f(0.0, 1.0, 1.0);
    drawObject3D(ballB.obj3D);

    // test draw bounding box
    glColor3f(1.0, 0.0, 0.0);
    drawBoundingBox(ballB.bBox);



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

    case 'g':
        activateGrav = 1;
        printf("grva = %d", activateGrav);
        break;
    case 'v':
        printf("Ball a x velocity: %f", ballA.physics.velocity.x);
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

    camera.center = normalize(camera.center);

    glutPostRedisplay();
}

void animate()
{
    glutTimerFunc(TIMERSEC, animate, 0);
    if (activateGrav == 1){
        //Apply gravity for ball A
        CalcGravity(&ballA.physics, TIMERSEC);
        //Apply changes in position
        ChangePosition(&ballA.physics);
        //Bounce off floor
        if(ballA.physics.position.y < -1) {
                    invertVelocityY(&ballA.physics);
                    ballA.physics.velocity.x = ballA.physics.velocity.x * 0.9;
                    ballA.physics.velocity.z = ballA.physics.velocity.z * 0.9;
        }

        //Apply gravity for ball B
        CalcGravity(&ballB.physics, TIMERSEC);
        //Apply changes in position
        ChangePosition(&ballB.physics);
        //Bounce off floor
        if(ballB.physics.position.y < -1){
            invertVelocityY(&ballB.physics);
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
    SetPhysics(&ballA.physics, 1);
    ballA.physics.velocity.x = 0.00001;
    SetPhysics(&ballB.physics, 1);
    ballB.physics.velocity.x = -0.00001;
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    init(); // initialize attributes
    glutDisplayFunc(display); // callback that is invoked when window is displayed
    glutKeyboardFunc(keys); // interaction with keyboard keys
    glutPassiveMotionFunc(mouseMove); // interaction with moving the mouse
    glutMotionFunc(mouseMove); // interaction with moving the mouse (onClicked)

    glutIdleFunc(animate);
    glutMainLoop(); // enter event loop

    // Free objects from memory
    freeObject3D(ballA.obj3D);
    freeObject3D(ballB.obj3D);

    return 0;
}
