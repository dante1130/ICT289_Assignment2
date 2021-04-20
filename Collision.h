#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

// for test drawing, will be removed
#include <gl/freeglut.h>
#include <stdbool.h>
#include "BoundingBox.h"
#include "BoundingSphere.h"

bool isSphereCollide(BoundingSphere sphere1, BoundingSphere sphere2);
bool isBoxCollide(BoundingBox box1, BoundingBox box2);

void drawBoundingBox(BoundingBox box); // for test drawing, will be removed

#endif // COLLISION_H_INCLUDED
