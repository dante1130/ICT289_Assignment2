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

bool isBoxCollidePoint(BoundingBox box, Vector3 point)
{
    return (point.x >= box.minExtent.x && point.x <= box.maxExtent.x) &&
           (point.y >= box.minExtent.y && point.y <= box.maxExtent.y) &&
           (point.z >= box.minExtent.z && point.z <= box.maxExtent.z);
}

bool isBoxCollideSphere(BoundingBox box, BoundingSphere sphere)
{
    float distance;
    Vector3 point;

    point.x = (sphere.center.x < box.maxExtent.x) ? sphere.center.x : box.maxExtent.x;
    point.y = (sphere.center.y < box.maxExtent.y) ? sphere.center.y : box.maxExtent.y;
    point.z = (sphere.center.z < box.maxExtent.z) ? sphere.center.z : box.maxExtent.z;

    point.x = (box.minExtent.x > point.x) ? box.minExtent.x : point.x;
    point.y = (box.minExtent.y > point.y) ? box.minExtent.y : point.y;
    point.z = (box.minExtent.z > point.z) ? box.minExtent.z : point.z;

    distance = magnitude(subtract(point, sphere.center));

    return distance <= sphere.radius;
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
