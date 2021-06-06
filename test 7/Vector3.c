#include "Vector3.h"

Vector3 add(Vector3 vector1, Vector3 vector2)
{
    Vector3 vector;

    vector.x = vector1.x + vector2.x;
    vector.y = vector1.y + vector2.y;
    vector.z = vector1.z + vector2.z;

    return vector;
}

Vector3 subtract(Vector3 vector1, Vector3 vector2)
{
    Vector3 vector;

    vector.x = vector1.x - vector2.x;
    vector.y = vector1.y - vector2.y;
    vector.z = vector1.z - vector2.z;

    return vector;
}

Vector3 multiply(Vector3 vector, float scalar)
{
    vector.x *= scalar;
    vector.y *= scalar;
    vector.z *= scalar;

    return vector;
}

Vector3 divide(Vector3 vector, float scalar)
{
    vector.x /= scalar;
    vector.y /= scalar;
    vector.z /= scalar;

    return vector;
}

float magnitude(Vector3 vector)
{
    return (float) sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

Vector3 normalize(Vector3 vector)
{
    float vectorMagnitude = magnitude(vector);

    vector.x /= vectorMagnitude;
    vector.y /= vectorMagnitude;
    vector.z /= vectorMagnitude;

    return vector;
}

float dotProduct(Vector3 vector1, Vector3 vector2)
{
    return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
}

Vector3 crossProduct(Vector3 vector1, Vector3 vector2)
{
    Vector3 vector;

    vector.x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
    vector.y = (vector1.z * vector2.x) - (vector1.x * vector2.z);
    vector.z = (vector1.x * vector2.y) - (vector1.y * vector2.x);

    return vector;
}
