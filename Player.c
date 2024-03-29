#include "Player.h"

void playerInit(Player *player)
{
    player->bullet = readOFFFile("Objects/ball.off");
    player->weapon = readOFFFile("Objects/gun2.off");

    setColor(&player->weapon, 0.35, 0.35, 0.35);

    ResetCamera(&player->camera);
    vectorInit(&player->bullets);
}

void bulletInit(GameObject *bullet)
{
    SetPhysics(&bullet->physics, 1);
    getBoundingSphere(bullet->obj3D, &bullet->bSphere.center, &bullet->bSphere.radius);
    setColor(&bullet->obj3D, 1, 0, 0);
}

void drawGun(const Player *player)
{
    glPushMatrix();
    glTranslatef(player->camera.eye.x + player->camera.center.x,
                 player->camera.eye.y + player->camera.center.y - 0.25,
                 player->camera.eye.z + player->camera.center.z);
    glRotatef(-player->camera.yaw, 0, 1, 0);
    glRotatef(player->camera.pitch, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    drawObject3D(player->weapon);
    glPopMatrix();
}

void shoot(Player *player, float time)
{
    GameObject *bullet = (GameObject *) malloc(sizeof(GameObject));

    bullet->obj3D = player->bullet;

    bulletInit(bullet);

    bullet->physics.position = player->camera.eye;
    bullet->physics.velocity = multiply(player->camera.center, time);

    vectorPush(&player->bullets, bullet);
}

void freePlayer(Player *player)
{

}
