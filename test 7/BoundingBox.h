#ifndef BOUNDINGBOX_H_INCLUDED
#define BOUNDINGBOX_H_INCLUDED

#include "Vector3.h"

typedef struct BoundingBox
{
    /// The bottom left corner of the box
    Vector3 minExtent;

    /// The top right corner of the box
    Vector3 maxExtent;
} BoundingBox;

#endif // BOUNDINGBOX_H_INCLUDED
