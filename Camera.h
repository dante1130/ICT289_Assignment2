#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Vector3.h"

/** \struct Camera
 *
 * A struct used to be used in conjunction
 * with the function gluLookAt by storing
 * its parameters in the struct, it also
 * contains function that simulates movement.
 *
 */
typedef struct Camera
{
    Vector3 eye;
    Vector3 center;
    Vector3 up;
} Camera;

/** \brief Creates a camera object.
 *
 * \return Camera object
 *
 */
Camera CreateCamera();

/** \brief Sets the camera to default values.
 *
 * \param Camera *
 * \return void
 *
 */
void ResetCamera(Camera *camera);

/** \brief Moves the camera forward.
 *
 * Moves the camera forward by subtracting its z position
 * with a speed value.
 *
 * \param Camera *
 * \param float
 * \return void
 *
 */
void MoveForward(Camera *camera, float speed);

/** \brief Moves the camera backward.
 *
 * Moves the camera forward by adding its z position
 * with a speed value.
 *
 * \param Camera *
 * \param float
 * \return void
 *
 */
void MoveBackward(Camera *camera, float speed);

/** \brief Moves the camera left.
 *
 * Moves the camera forward by subtracting its x position
 * with a speed value.
 *
 * \param Camera *
 * \param float
 * \return void
 *
 */
void MoveLeft(Camera *camera, float speed);

/** \brief Moves the camera right.
 *
 * Moves the camera forward by adding its x position
 * with a speed value.
 *
 * \param Camera *
 * \param float
 * \return void
 *
 */
void MoveRight(Camera *camera, float speed);

#endif // CAMERA_H_INCLUDED
