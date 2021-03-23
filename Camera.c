#include "Camera.h"
#include <stdio.h>

Camera CreateCamera()
{
    Camera camera;

    // Assign default values
    ResetCamera(&camera);

    return camera;
}

void ResetCamera(Camera *camera)
{
    camera->eye.x = 0;
    camera->eye.y = 0;
    camera->eye.z = 5;

    camera->center.x = 0;
    camera->center.y = 0;
    camera->center.z = 0;

    camera->up.x = 0;
    camera->up.y = 1;
    camera->up.z = 0;
}

void MoveForward(Camera *camera, float speed)
{
    camera->eye.z -= speed;
    camera->center.z -= speed;
}

void MoveBackward(Camera *camera, float speed)
{
    camera->eye.z += speed;
    camera->center.z += speed;
}

void MoveLeft(Camera *camera, float speed)
{
    camera->eye.x -= speed;
    camera->center.x -= speed;
}

void MoveRight(Camera *camera, float speed)
{
    camera->eye.x += speed;
    camera->center.x += speed;
}
