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
    GLfloat color[3];
} Object3D;

void setColor(Object3D * obj3D, float red, float green, float blue);

void normalizeObject3D(Object3D *obj3D);

Vector3 getCenterOfMass(Object3D obj3D);

float getBoundingSphereRadius(Object3D obj3D);

void getBoundingSphere(Object3D obj3D, Vector3 *center, float *radius);

void getBoundingBoxExtents(Object3D obj3D, Vector3 *minExtent, Vector3 *maxExtent);

void drawObject3D(Object3D obj3D);

void drawWorld(Object3D world);

void freeObject3D(Object3D *obj3D);


#endif // DATASTRUCTURES_H_INCLUDED
