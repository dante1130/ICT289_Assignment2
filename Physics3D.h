#ifndef PHYSICS3D_H_INCLUDED
#define PHYSICS3D_H_INCLUDED

#include "Vector3.h"

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

void ChangePosition(Physics3D *p);

void invertVelocityY(Physics3D *p);

void NewProjection(Physics3D *obj1, Physics3D *obj2);

#endif // PHYSICS3D_H_INCLUDED
