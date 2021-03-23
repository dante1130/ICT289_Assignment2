#include "Vector3.h"

Vector3 Add(Vector3 vector1, Vector3 vector2)
{
    Vector3 vector;

    vector.x = vector1.x + vector2.x;
    vector.y = vector1.y + vector2.y;
    vector.z = vector1.z + vector2.z;

    return vector;
}

Vector3 Substract(Vector3 vector1, Vector3 vector2)
{
    Vector3 vector;

    vector.x = vector1.x - vector2.x;
    vector.y = vector1.y - vector2.y;
    vector.z = vector1.z - vector2.z;

    return vector;
}

Vector3 Multiply(Vector3 vector, int scalar)
{
    vector.x *= scalar;
    vector.y *= scalar;
    vector.z *= scalar;

    return vector;
}

Vector3 Divide(Vector3 vector, int scalar)
{
    vector.x /= scalar;
    vector.y /= scalar;
    vector.z /= scalar;

    return vector;
}

float Magnitude(Vector3 vector)
{
    return (float) sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

Vector3 Normalize(Vector3 vector)
{
    float magnitude = Magnitude(vector);

    vector.x /= magnitude;
    vector.y /= magnitude;
    vector.z /= magnitude;

    return vector;
}

float DotProduct(Vector3 vector1, Vector3 vector2)
{
    return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
}

Vector3 CrossProduct(Vector3 vector1, Vector3 vector2)
{
    Vector3 vector;

    vector.x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
    vector.y = (vector1.z * vector2.x) - (vector1.x * vector2.z);
    vector.z = (vector1.x * vector2.y) - (vector1.y * vector2.x);

    return vector;
}
