#include "BoundingSphere.h"

bool isCollide(BoundingSphere sphere1, BoundingSphere sphere2)
{
    float radiusDistance = sphere1.radius + sphere2.radius;
    float centerDistance = Magnitude(Subtract(sphere2.center, sphere1.center));

    return centerDistance <= radiusDistance;
}
