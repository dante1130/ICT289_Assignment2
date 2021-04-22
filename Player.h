#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <gl/freeglut.h>
#include "Camera.h"
#include "GameObject.h"

typedef struct Player
{
    Camera camera;
    Object3D weapon;
    GameObject bullet;
} Player;

void playerInit(Player *player);
void drawGun(Player *player);
void shoot(Player *player);

#endif // PLAYER_H_INCLUDED
