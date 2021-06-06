#include "GameObject.h"

void updateGameObj(GameObject * gameObject, float time)
{
    //Apply gravity
    CalcGravity(&gameObject->physics, time);

    //Apply changes in position
    ChangePosition(&gameObject->physics, time);

    // Update collision position
    gameObject->bBox.minExtent = add(gameObject->bBox.minExtent, multiply(gameObject->physics.velocity, time));
    gameObject->bBox.maxExtent = add(gameObject->bBox.maxExtent, multiply(gameObject->physics.velocity, time));

    gameObject->bSphere.center = gameObject->physics.position;
}


void translateGameObj(GameObject * gameObject, float x, float y, float z)
{
    Vector3 translate;

    translate.x = x;
    translate.y = y;
    translate.z = z;

    gameObject->physics.position = add(gameObject->physics.position, translate);

    gameObject->bBox.minExtent = add(gameObject->bBox.minExtent, translate);
    gameObject->bBox.maxExtent = add(gameObject->bBox.maxExtent, translate);

    gameObject->bSphere.center = add(gameObject->bSphere.center, translate);
}
