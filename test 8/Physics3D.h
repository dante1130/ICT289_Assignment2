#ifndef PHYSICS3D_H_INCLUDED
#define PHYSICS3D_H_INCLUDED

#include "Vector3.h"
#include "BoundingBox.h"

typedef struct Physics{

    Vector3 position;
    Vector3 velocity;
    Vector3 accel;
    float gravity;
    float mass;
    float elasticity;

}Physics3D;

void SetPhysics(Physics3D *p, float mass);

void CalcGravity(Physics3D *p, float time);

void ChangePosition(Physics3D *p, float time);

void GroundFriction(Physics3D *p);

void invertVelocityY(Physics3D *p);

void NewProjection(Physics3D *obj1, Physics3D *obj2);

void WorldCollideProjection(Physics3D *obj, BoundingBox wall);

#endif // PHYSICS3D_H_INCLUDED
