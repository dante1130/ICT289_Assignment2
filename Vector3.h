#ifndef VERTEX3_H_INCLUDED
#define VERTEX3_H_INCLUDED

typedef struct Vector3
{
    float x, y, z;
} Vector3;

Vector3 Add(Vector3 vector1, Vector3 vector2);
Vector3 Substract(Vector3 vector1, Vector3 vector2);
Vector3 Multiply(Vector3 vector, int scalar);
Vector3 Divide(Vector3 vector, int scalar);

float Magnitude(Vector3 vector);
Vector3 Normalize(Vector3 vector);

float DotProduct(Vector3 vector1, Vector3 vector2);
Vector3 CrossProduct(Vector3 vector1, Vector3 vector2);


#endif // VERTEX3_H_INCLUDED
