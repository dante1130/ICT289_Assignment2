#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <gl/freeglut.h>
#include "Camera.h"
#include "GameObject.h"
#include "VectorGameObject.h"
#include "OffLoader.h"

typedef struct Player
{
    Camera camera;
    Object3D weapon;
    Object3D bullet;
    VectorGameObject bullets;

} Player;

void playerInit(Player *player);
void bulletInit(GameObject *bullet);
void drawGun(const Player *player);
void drawBullets(const Player *player);
void shoot(Player *player, float time);
void freePlayer(Player *player);

#endif // PLAYER_H_INCLUDED
