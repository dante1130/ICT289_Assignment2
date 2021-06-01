#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Vector3.h"
#include "Object3D.h"
#include "Collision.h"
#include "Physics3D.h"

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

void initGameObj(GameObject * gameObject);
void updateGameObj(GameObject * gameObject, float time);
void translateGameObj(GameObject * gameObject, float x, float y, float z);

#endif // GAMEOBJECT_H_INCLUDED
