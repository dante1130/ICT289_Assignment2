#include <stdio.h>
#include "Object3D.h"

void drawObject3D(Object3D obj3D)
{
    for (int i = 0; i < obj3D.nfaces; ++i)
    {
        glBegin(GL_POLYGON);
            glVertex3f(obj3D.vertices[obj3D.faces[i].points[0]].x, obj3D.vertices[obj3D.faces[i].points[0]].y, obj3D.vertices[obj3D.faces[i].points[0]].z);
            glVertex3f(obj3D.vertices[obj3D.faces[i].points[1]].x, obj3D.vertices[obj3D.faces[i].points[1]].y, obj3D.vertices[obj3D.faces[i].points[1]].z);
            glVertex3f(obj3D.vertices[obj3D.faces[i].points[2]].x, obj3D.vertices[obj3D.faces[i].points[2]].y, obj3D.vertices[obj3D.faces[i].points[2]].z);
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
