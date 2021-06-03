#include "VectorGameObject.h"

void vectorInit(VectorGameObject *vector)
{
    vector->size = 0;
    vector->capacity = 16;
    vector->array = (GameObject *) malloc(vector->capacity * sizeof(GameObject));
}

void vectorPush(VectorGameObject *vector, const GameObject *gameObject)
{
    if (vector->size >= vector->capacity)
    {
        vector->capacity *= 1.5;
        vector->array = (GameObject *) realloc(vector->array, vector->capacity);
    }

    vector->array[vector->size] = *gameObject;
    ++vector->size;
}

void vectorDrawObj(const VectorGameObject *vector)
{
    for (int i = 0; i < vector->size; ++i)
    {
        glPushMatrix();
        glTranslatef(vector->array[i].physics.position.x,
                     vector->array[i].physics.position.y,
                     vector->array[i].physics.position.z);
        drawObject3D(vector->array[i].obj3D);
        glPopMatrix();
    }
}

void vectorDelete(VectorGameObject *vector)
{
    free(vector->array);

    vector->array = 0;
    vector->size = 0;
    vector->capacity = 0;
}
