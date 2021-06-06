#ifndef PHYSICS3D_H_INCLUDED
#define PHYSICS3D_H_INCLUDED

#include "Vector3.h"
#include "Object3D.h"
typedef struct Physics{

    Vector3 position;
    Vector3 velocity;
    Vector3 accel;
    Vector3 rotation;
    float gravity;
    float mass;
    float elasticity;

}Physics3D;

void SetPhysics(Physics3D *p, float mass);

void CalcGravity(Physics3D *p, float time);

void ChangePosition(Physics3D *p, float time);

void invertVelocityY(Physics3D *p);

void NewProjection(Physics3D *obj1, Physics3D *obj2);

void GroundFriction(Physics3D *obj1);

Vector3 CalculateRotation(Physics3D *base, Physics3D collider);

void ApplyRotation(Physics3D *base, Vector3 tempRotate, float time);

void ReduceRotation(Physics3D *base, Vector3 *tempRotate);
#endif // PHYSICS3D_H_INCLUDED
