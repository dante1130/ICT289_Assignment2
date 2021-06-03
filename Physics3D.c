#include "Physics3D.h"

void SetPhysics(Physics3D *p, float mass)
{
    p->gravity = -9.807;
    p->elasticity = -0.5;
    p->mass = mass;

    p->velocity.x = 0;
    p->velocity.y = 0;
    p->velocity.z = 0;

    p->accel.x = 0;
    p->accel.y = p->gravity;
    p->accel.z = 0;

    p->position.x = 0;
    p->position.y = 0;
    p->position.z = 0;
}

void CalcGravity(Physics3D *p, float time)
{
    p->velocity = add(p->velocity, multiply(p->accel, time));
}

void invertVelocityY(Physics3D *p)
{
    p->velocity.y *= p->elasticity;
}

void ChangePosition(Physics3D *p, float time)
{
    p->position = add(p->position, multiply(p->velocity, time));
}

void GroundFriction(Physics3D *p)
{
    if (p->velocity.x > 0.1)
    {
        p->velocity.x -= 0.02;
    }
    else if (p->velocity.x < -0.1)
    {
        p->velocity.x += 0.02;
    }
    else
    {
        p->velocity.x = 0;
    }

    if (p->velocity.z > 0.1)
    {
        p->velocity.z -= 0.02;
    }
    else if (p->velocity.z < -0.1)
    {
        p->velocity.z += 0.02;
    }
    else
    {
        p->velocity.z = 0;
    }
}

void NewProjection(Physics3D *obj1, Physics3D *obj2)
{
    float massSum = obj1->mass + obj2->mass;

    obj1->velocity = multiply(obj2->velocity, (obj2->mass / massSum));
    obj2->velocity = multiply(obj1->velocity, (obj1->mass / massSum));
}
