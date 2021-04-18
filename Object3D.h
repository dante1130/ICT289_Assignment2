#ifndef DATASTRUCTURES_H_INCLUDED
#define DATASTRUCTURES_H_INCLUDED

#include <stdlib.h>
#include <math.h>
#include <GL/freeglut.h>
#include "Vector3.h"

typedef struct Faces
{
    int numPoints;
    GLint *points;
} Faces;

typedef struct Object3D
{
    int nvert;
    int nfaces;
    Vector3 *vertices;
    Faces *faces;
} Object3D;

Vector3 GetCenterOfMass(Object3D obj3D);

float GetBoundingSphereRadius(Object3D obj3D);

void drawObject3D(Object3D obj3D);

void freeObject3D(Object3D obj3D);


#endif // DATASTRUCTURES_H_INCLUDED
