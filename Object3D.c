#include <stdio.h>
#include "Object3D.h"

void drawObject3D(Object3D obj3D)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < obj3D.nvert; i++)
    {
        glVertex3f(obj3D.vertices[i].x, obj3D.vertices[i].y, obj3D.vertices[i].z);
    }
    glEnd();
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
