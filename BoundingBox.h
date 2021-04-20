#ifndef BOUNDINGBOX_H_INCLUDED
#define BOUNDINGBOX_H_INCLUDED

// for test drawing only, will be removed.
#include <gl/freeglut.h>

#include <stdbool.h>
#include "Vector3.h"

typedef struct BoundingBox
{
    /// The bottom left corner of the box
    Vector3 minExtent;

    /// The top right corner of the box
    Vector3 maxExtent;
} BoundingBox;

// for test drawing only, will be removed.
void drawBoundingBox(BoundingBox box);
bool isBoxCollide(BoundingBox box1, BoundingBox box2);

#endif // BOUNDINGBOX_H_INCLUDED
