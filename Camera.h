#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Vector3.h"

typedef struct Camera
{
    Vector3 eye;
    Vector3 center;
    Vector3 up;
} Camera;

Camera CreateCamera();
void ResetCamera(Camera *camera);

void MoveForward(Camera *camera, float speed);
void MoveBackward(Camera *camera, float speed);
void MoveLeft(Camera *camera, float speed);
void MoveRight(Camera *camera, float speed);

#endif // CAMERA_H_INCLUDED
