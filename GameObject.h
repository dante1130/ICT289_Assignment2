#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Vector3.h"
#include "Object3D.h"
#include "Collision.h"

/** \struct GameObject
 *
 * Represents a game object, used to represent
 * an object's position in the 3D plane, along
 * with the properties of its physics and collision.
 *
 */
typedef struct GameObject
{
    Object3D obj3D;
    BoundingBox bBox;
    BoundingSphere bSphere;
    Physics3D physics;

} GameObject;

#endif // GAMEOBJECT_H_INCLUDED
