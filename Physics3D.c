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

void GroundFriction(Physics3D *obj1)
{
    if(obj1->velocity.x > 0.1)
        obj1->velocity.x -= 0.03;
    else if(obj1->velocity.x < -0.1)
        obj1->velocity.x += 0.03;
    else
        obj1->velocity.x = 0;

    if(obj1->velocity.z > 0.1)
        obj1->velocity.z -= 0.03;
    else if(obj1->velocity.z < -0.1)
        obj1->velocity.z += 0.03;
    else
        obj1->velocity.z = 0;
}

Vector3 CalculateRotation(Physics3D *base, Physics3D collider)
{
    Vector3 torque;
    Vector3 rotation;

    //finds the distance of colliding object and base objects center of mass
    Vector3 distance = subtract(collider.position, base->position);

    if (collider.velocity.z < 0)
        collider.velocity.z *= -1;
    if (collider.velocity.x < 0)
        collider.velocity.x *= -1;

    //determines the torque applied to the bottle
    torque.x = distance.y * collider.velocity.z * -1;
    torque.y = 0;
    torque.z = distance.y * collider.velocity.x * -1;

    //calculates rotation needed based on force
    rotation = multiply(torque, 30);
    return rotation;
}

void ReduceRotation(Physics3D *base, Vector3 *tempRotate)
{
    int angleX = (int)base->rotation.x % 360;
    int angleZ = (int)base->rotation.z % 360;

    if (angleX < -330 )
        tempRotate->x = (base->rotation.x - angleX) - 0;
    else if ((angleX >= -330) && (angleX <= -180))
        tempRotate->x = (base->rotation.x - angleX) - 270;
    else if (angleX  < -30)
        tempRotate->x = (base->rotation.x - angleX) - 90;
    else if (((angleX < 30 )) || (angleX > 330 ))
        tempRotate->x = (base->rotation.x - angleX) + 0;
    else if (angleX  <= 180 )
        tempRotate->x = (base->rotation.x - angleX) + 90;
    else if (angleX  <= 330 )
        tempRotate->x = (base->rotation.x - angleX) + 270;

    if (angleZ < -330 )
        tempRotate->z = (base->rotation.z - angleZ) - 0;
    else if ((angleZ >= -330) && (angleZ <= -180))
        tempRotate->z = (base->rotation.z - angleZ) - 270;
    else if (angleZ  < -30)
        tempRotate->z = (base->rotation.z - angleZ) - 90;
    else if (((angleZ < 30 )) || (angleZ > 330 ))
        tempRotate->z = (base->rotation.z - angleZ) + 0;
    else if (angleZ <= 180 )
        tempRotate->z = (base->rotation.z - angleZ) + 90;
    else if (angleZ  <= 330 )
        tempRotate->z = (base->rotation.z - angleZ) + 270;
}

void ApplyRotation(Physics3D *base, Vector3 tempRotate, float time)
{
    if (base->rotation.x < tempRotate.x)
        base->rotation.x += 3;
    if (base->rotation.x > tempRotate.x)
        base->rotation.x -= 3;
    if (base->rotation.z < tempRotate.z)
        base->rotation.z += 3;
    if (base->rotation.z > tempRotate.z)
        base->rotation.z -= 3;
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
