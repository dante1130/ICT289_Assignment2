#include "Camera.h"

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
    Vector3 crossProduct = CrossProduct(camera->center, camera->up);

    camera->eye.x -= crossProduct.x * speed;
    camera->eye.z -= crossProduct.z * speed;
}

void MoveRight(Camera *camera, float speed)
{
    Vector3 crossProduct = CrossProduct(camera->center, camera->up);

    camera->eye.x += crossProduct.x * speed;
    camera->eye.z += crossProduct.z * speed;
}

void LookLeft(Camera *camera)
{
    camera->angle -= 0.05f;
    camera->center.x = sin(camera->angle);
    camera->center.z = -cos(camera->angle);
}

void LookRight(Camera *camera)
{
    camera->angle += 0.05f;
    camera->center.x = sin(camera->angle);
    camera->center.z = -cos(camera->angle);
}
