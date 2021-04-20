#ifndef BOUNDINGSPHERE_H_INCLUDED
#define BOUNDINGSPHERE_H_INCLUDED

#include "Vector3.h"

typedef struct BoundingSphere
{
    Vector3 center;
    float radius;

} BoundingSphere;

#endif // BOUNDINGSPHERE_H_INCLUDED
