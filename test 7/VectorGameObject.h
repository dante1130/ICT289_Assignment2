#ifndef VECTORGAMEOBJECT_H_INCLUDED
#define VECTORGAMEOBJECT_H_INCLUDED

#include "GameObject.h"

typedef struct VectorGameObject
{
    GameObject *array;
    int size;
    int capacity;
} VectorGameObject;

void vectorInit(VectorGameObject *vector);
void vectorPush(VectorGameObject *vector, const GameObject *gameObject);
void vectorDrawObj(const VectorGameObject *vector);
void vectorDelete(VectorGameObject *vector);

#endif // VECTORGAMEOBJECT_H_INCLUDED
