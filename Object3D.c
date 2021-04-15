#include <stdio.h>
#include "Object3D.h"

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
