#include "Player.h"

void playerInit(Player *player)
{
    Vector3 center = getCenterOfMass(player->weapon);

    ResetCamera(&player->camera);
    vectorInit(&player->bullets);
}

void bulletInit(GameObject *bullet)
{
    bullet->obj3D = readOFFFile("Objects/ball.off");
    SetPhysics(&bullet->physics, 0.1);
    getBoundingSphere(bullet->obj3D, &bullet->bSphere.center, &bullet->bSphere.radius);
    setColor(&bullet->obj3D, 0, 0, 1.0);
}

void drawGun(Player *player)
{
    glPushMatrix();
    glTranslatef(player->camera.eye.x + player->camera.center.x,
                 player->camera.eye.y + player->camera.center.y,
                 player->camera.eye.z + player->camera.center.z);
    glRotatef(90, 0, 1, 0);
    drawObject3D(player->weapon);
    glPopMatrix();
}

void shoot(Player *player, float time)
{
    GameObject bullet;

    bulletInit(&bullet);

    bullet.physics.position = player->camera.eye;
    bullet.physics.velocity = multiply(player->camera.center, time);

    vectorPush(&player->bullets, &bullet);
}
