#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include <GL/freeglut.h>
#include "Collision.h"

typedef float point3[3];

typedef struct Wall
{
    BoundingBox bPlanes[10];
} Wall;

void drawWalls();

void readPlanes(Wall *wall);

#endif // WALL_H_INCLUDED
