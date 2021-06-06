#include "Camera.h"

void ResetCamera(Camera *camera)
{
    camera->eye.x = 0;
    camera->eye.y = 1;
    camera->eye.z = 2;

    camera->center.x = 0;
    camera->center.y = 0;
    camera->center.z = 0;

    camera->up.x = 0;
    camera->up.y = 1;
    camera->up.z = 0;

    camera->yaw = 0;
    camera->pitch = 0;

    camera->angle = 0;
}

void MoveForward(Camera *camera, float speed)
{
    camera->eye.x += camera->center.x * speed;
    camera->eye.z += camera->center.z * speed;
}

void MoveBackward(Camera *camera, float speed)
{
    camera->eye.x -= camera->center.x * speed;
    camera->eye.z -= camera->center.z * speed;
}

void MoveLeft(Camera *camera, float speed)
{
    Vector3 crossP = crossProduct(camera->center, camera->up);

    camera->eye.x -= crossP.x * speed;
    camera->eye.z -= crossP.z * speed;
}

void MoveRight(Camera *camera, float speed)
{
    Vector3 crossP = crossProduct(camera->center, camera->up);

    camera->eye.x += crossP.x * speed;
    camera->eye.z += crossP.z * speed;
}
