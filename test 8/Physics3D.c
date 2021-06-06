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
        p->velocity.x -= 0.04;
    }
    else if (p->velocity.x < -0.1)
    {
        p->velocity.x += 0.04;
    }
    else
    {
        p->velocity.x = 0;
    }

    if (p->velocity.z > 0.1)
    {
        p->velocity.z -= 0.04;
    }
    else if (p->velocity.z < -0.1)
    {
        p->velocity.z += 0.04;
    }
    else
    {
        p->velocity.z = 0;
    }
}

void NewProjection(Physics3D *obj1, Physics3D *obj2)
{
    float massSum = obj1->mass + obj2->mass;
    Vector3 temp1 = obj1->velocity;
    obj1->velocity = add(multiply(obj1->velocity, ((obj1->mass - obj2->mass) / massSum)),
                         multiply(obj2->velocity, ((2 * obj2->mass) / massSum)));
    obj2->velocity = add(multiply(obj2->velocity, ((obj2->mass - obj1->mass) / massSum)),
                         multiply(temp1, ((2 * obj1->mass) / massSum)));
}

void WorldCollideProjection(Physics3D *obj, BoundingBox wall)
{
    Vector3 theta = subtract(wall.maxExtent, wall.minExtent);

    if((theta.x < 0.2) && (theta.x > -0.2))
        obj->velocity.x *= -0.9;
    else if((theta.y < 0.2) && (theta.y > -0.2))
        obj->velocity.y *= -0.9;
    else if((theta.z < 0.2) && (theta.z > -0.2))
        obj->velocity.z *= -0.9;

}
