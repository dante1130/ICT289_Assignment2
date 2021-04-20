#include <stdio.h>
#include "Object3D.h"

Vector3 GetCenterOfMass(Object3D obj3D)
{
    Vector3 sum;

    sum.x = 0;
    sum.y = 0;
    sum.z = 0;

    for (int i = 0; i < obj3D.nvert; ++i)
    {
        sum = Add(sum, obj3D.vertices[i]);
    }

    return Divide(sum, obj3D.nvert);
}

float GetBoundingSphereRadius(Object3D obj3D)
{
    Vector3 centerOfMass = GetCenterOfMass(obj3D);

    float magnitude;
    float radius = 0;

    for (int i = 0; i < obj3D.nvert; ++i)
    {
        magnitude = Magnitude(Subtract(obj3D.vertices[i], centerOfMass));

        if (radius < magnitude)
        {
            radius = magnitude;
        }
    }

    return radius;
}

void GetBoundingBoxExtents(Object3D obj3D, Vector3 *minExtent, Vector3 *maxExtent)
{
    Vector3 center = GetCenterOfMass(obj3D);
    float magnitude = Magnitude(Subtract(obj3D.vertices[0], center));
    float max = magnitude;
    float min = magnitude;

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
