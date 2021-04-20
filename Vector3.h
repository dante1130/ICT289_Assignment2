#ifndef VERTEX3_H_INCLUDED
#define VERTEX3_H_INCLUDED

#include <math.h>

/** \struct Vector3
 *
 * Represents a displacement in a 3D space.
 *
 */
typedef struct Vector3
{
    float x, y, z;
} Vector3;

/** \brief Adds the values of 2 vectors.
 *
 * \param Vector3
 * \param Vector3
 * \return Vector3
 *
 */
Vector3 add(Vector3 vector1, Vector3 vector2);

/** \brief Subtracts the values of 2 vectors.
 *
 * \param Vector3
 * \param Vector3
 * \return Vector3
 *
 */
Vector3 subtract(Vector3 vector1, Vector3 vector2);

/** \brief Multiply the values of a vector by a scalar.
 *
 * \param Vector3
 * \param Vector3
 * \return Vector3
 *
 */
Vector3 multiply(Vector3 vector, int scalar);

/** \brief Divide the values of a vector by a scalar.
 *
 * \param Vector3
 * \param Vector3
 * \return Vector3
 *
 */
Vector3 divide(Vector3 vector, int scalar);

/** \brief Calculates the magnitude of a vector.
 *
 * \param Vector3
 * \return float
 *
 */
float magnitude(Vector3 vector);

/** \brief Normalizes the vector.
 *
 * \param Vector3
 * \return Vector3
 *
 */
Vector3 normalize(Vector3 vector);

/** \brief Calculates the dot product of 2 vectors.
 *
 * \param Vector3
 * \param Vector3
 * \return float
 *
 */
float dotProduct(Vector3 vector1, Vector3 vector2);

/** \brief Calculates the cross product of 2 vectors.
 *
 * \param Vector3
 * \param Vector3
 * \return Vector3
 *
 */
Vector3 crossProduct(Vector3 vector1, Vector3 vector2);


#endif // VERTEX3_H_INCLUDED
