#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Vector3.h"

/** \struct GameObject
 *
 * Represents a game object, used to represent
 * an object's position in the 3D plane.
 *
 */
typedef struct GameObject
{
    Vector3 position;
    // velocity? direction?
} GameObject

#endif // GAMEOBJECT_H_INCLUDED
