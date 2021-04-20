#include <stdio.h>
#include "Object3D.h"

Vector3 getCenterOfMass(Object3D obj3D)
{
    Vector3 sum;

    sum.x = 0;
    sum.y = 0;
    sum.z = 0;

    for (int i = 0; i < obj3D.nvert; ++i)
    {
        sum = add(sum, obj3D.vertices[i]);
    }

    return divide(sum, obj3D.nvert);
}

float getBoundingSphereRadius(Object3D obj3D)
{
    Vector3 centerOfMass = getCenterOfMass(obj3D);

    float distance;
    float radius = 0;

    for (int i = 0; i < obj3D.nvert; ++i)
    {
        distance = magnitude(subtract(obj3D.vertices[i], centerOfMass));

        if (radius < distance)
        {
            radius = distance;
        }
    }

    return radius;
}

void getBoundingBoxExtents(Object3D obj3D, Vector3 *minExtent, Vector3 *maxExtent)
{
    *minExtent = obj3D.vertices[0];
    *maxExtent = obj3D.vertices[0];

    for (int i = 1; i < obj3D.nvert; ++i)
    {
        minExtent->x = (obj3D.vertices[i].x < minExtent->x) ? obj3D.vertices[i].x : minExtent->x;
        minExtent->y = (obj3D.vertices[i].y < minExtent->y) ? obj3D.vertices[i].y : minExtent->y;
        minExtent->z = (obj3D.vertices[i].z < minExtent->z) ? obj3D.vertices[i].z : minExtent->z;

        maxExtent->x = (obj3D.vertices[i].x > maxExtent->x) ? obj3D.vertices[i].x : maxExtent->x;
        maxExtent->y = (obj3D.vertices[i].y > maxExtent->y) ? obj3D.vertices[i].y : maxExtent->y;
        maxExtent->z = (obj3D.vertices[i].z > maxExtent->z) ? obj3D.vertices[i].z : maxExtent->z;
    }
}

void normalizeObject3D(Object3D *obj3D)
{
    Vector3 center = getCenterOfMass(*obj3D);
    float radius = getBoundingSphereRadius(*obj3D);

    for (int i = 0; i < obj3D->nvert; ++i)
    {
        obj3D->vertices[i] = subtract(obj3D->vertices[i], center);
        obj3D->vertices[i] = divide(obj3D->vertices[i], radius);
    }
}

void drawObject3D(Object3D obj3D)
{
    for (int i = 0; i < obj3D.nfaces; ++i)
    {
        glBegin(GL_POLYGON);
            for (int j = 0; j < obj3D.faces[i].numPoints; ++j)
            {
                glVertex3f(obj3D.vertices[obj3D.faces[i].points[j]].x,
                           obj3D.vertices[obj3D.faces[i].points[j]].y,
                           obj3D.vertices[obj3D.faces[i].points[j]].z);
            }
        glEnd();
    }
}

void freeObject3D(Object3D obj3D)
{
    for (int i = 0; i < obj3D.nfaces; ++i)
    {
        free(obj3D.faces[i].points);
    }

    free(obj3D.faces);
    free(obj3D.vertices);
}
