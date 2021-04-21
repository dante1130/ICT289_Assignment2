#include "Collision.h"

bool isSphereCollide(BoundingSphere sphere1, BoundingSphere sphere2)
{
    float radiusDistance = sphere1.radius + sphere2.radius;
    float centerDistance = magnitude(subtract(sphere2.center, sphere1.center));

    return centerDistance <= radiusDistance;
}

bool isBoxCollide(BoundingBox box1, BoundingBox box2)
{
    return (box1.minExtent.x <= box2.maxExtent.x && box1.maxExtent.x >= box2.minExtent.x) &&
           (box1.minExtent.y <= box2.maxExtent.y && box1.maxExtent.y >= box2.minExtent.y) &&
           (box1.minExtent.z <= box2.maxExtent.z && box1.maxExtent.z >= box2.minExtent.z);
}

void drawBoundingBox(BoundingBox box)
{
    // Face 1
    glBegin(GL_LINE_LOOP);
        glVertex3f(box.minExtent.x, box.minExtent.y, box.minExtent.z); // btm left
        glVertex3f(box.maxExtent.x, box.minExtent.y, box.minExtent.z); // btm right
        glVertex3f(box.maxExtent.x, box.maxExtent.y, box.minExtent.z); // top right
        glVertex3f(box.minExtent.x, box.maxExtent.y, box.minExtent.z); // top left
    glEnd();

    // Face 2
    glBegin(GL_LINE_LOOP);
        glVertex3f(box.maxExtent.x, box.maxExtent.y, box.maxExtent.z); // top right
        glVertex3f(box.minExtent.x, box.maxExtent.y, box.maxExtent.z); // top left
        glVertex3f(box.minExtent.x, box.minExtent.y, box.maxExtent.z); // btm left
        glVertex3f(box.maxExtent.x, box.minExtent.y, box.maxExtent.z); // btm right
    glEnd();

    // Connect lines
    glBegin(GL_LINES);
        // btm left
        glVertex3f(box.minExtent.x, box.minExtent.y, box.minExtent.z);
        glVertex3f(box.minExtent.x, box.minExtent.y, box.maxExtent.z);

        // btm right
        glVertex3f(box.maxExtent.x, box.minExtent.y, box.minExtent.z);
        glVertex3f(box.maxExtent.x, box.minExtent.y, box.maxExtent.z);

        // top right
        glVertex3f(box.maxExtent.x, box.maxExtent.y, box.minExtent.z);
        glVertex3f(box.maxExtent.x, box.maxExtent.y, box.maxExtent.z);

        // top left
        glVertex3f(box.minExtent.x, box.maxExtent.y, box.minExtent.z);
        glVertex3f(box.minExtent.x, box.maxExtent.y, box.maxExtent.z);
    glEnd();
}
