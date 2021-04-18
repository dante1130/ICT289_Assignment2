#ifndef BOUNDINGSPHERE_H_INCLUDED
#define BOUNDINGSPHERE_H_INCLUDED

#include <stdbool.h>
#include "Vector3.h"


typedef struct BoundingSphere
{
    Vector3 center;
    float radius;

} BoundingSphere;

bool isCollide(BoundingSphere sphere1, BoundingSphere sphere2);

#endif // BOUNDINGSPHERE_H_INCLUDED
