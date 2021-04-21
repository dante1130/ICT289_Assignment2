#include "GameObject.h"

void updateGameObj(GameObject * gameObject, float time)
{
    //Apply gravity
    CalcGravity(&gameObject->physics, time);
    //Apply changes in position
    ChangePosition(&gameObject->physics);

    // Update collision position
    gameObject->bBox.minExtent = add(gameObject->bBox.minExtent, gameObject->physics.velocity);
    gameObject->bBox.maxExtent = add(gameObject->bBox.maxExtent, gameObject->physics.velocity);

    gameObject->bSphere.center = add(gameObject->bSphere.center, gameObject->physics.velocity);
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
