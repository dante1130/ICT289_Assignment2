#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <GL/freeglut.h>

typedef unsigned char pixel;       /* one byte (0 .. 255) for each pixel */

typedef struct Image
{
    pixel **image;
    int rows;
    int columns;
} Image;

void WriteCaptions();

void drawImage(Image *img, float x, float y);

void FlipImage(pixel *imageBuffer, Image *img);

void freeImage(Image *img);

#endif // IMAGE_H_INCLUDED
