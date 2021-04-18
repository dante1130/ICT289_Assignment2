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
