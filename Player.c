#include "Player.h"

void playerInit(Player *player)
{
    Vector3 center = getCenterOfMass(player->weapon);

    ResetCamera(&player->camera);
    SetPhysics(&player->bullet.physics, 0.1);
    getBoundingSphere(player->bullet.obj3D, &player->bullet.bSphere.center, &player->bullet.bSphere.radius);
}

void drawGun(Player *player)
{
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    glTranslatef(player->camera.eye.x + player->camera.center.x,
                 player->camera.eye.y + player->camera.center.y,
                 player->camera.eye.z + player->camera.center.z);
    glRotatef(90, 0, 1, 0);
    drawObject3D(player->weapon);
    glPopMatrix();
}

void shoot(Player *player)
{
    player->bullet.physics.position = player->camera.eye;
    player->bullet.physics.velocity = player->camera.center;
}
