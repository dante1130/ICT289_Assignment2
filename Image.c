#include "Image.h"

void WriteCaptions()
{
    char caption1[] = "Andrew Ho";
    char caption2[] = "Spencer Shaw";

    glColor3f(0.0, 0.0, 0.0);

    glRasterPos2i(320, 20);
    for (int i = 0; i < sizeof(caption1); i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, caption1[i]);

    glRasterPos2i(960, 20);
    for (int i = 0; i < sizeof(caption2); i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, caption2[i]);
}

void drawImage(Image *img, float x, float y)
{
    pixel image_buf[img->rows * img->columns];

    FlipImage(&image_buf, img);

    glRasterPos2f(x, y);
	glDrawPixels(img->rows, img->columns, GL_LUMINANCE, GL_UNSIGNED_BYTE, image_buf);
}

void FlipImage(pixel *imageBuffer, Image *img)
{
    int offset = 0;

    for (int row = img->rows-1; row >= 0; --row, ++offset)
    {
        for (int column = 0; column < img->columns; ++column)
        {
            imageBuffer[img->columns * offset + column] = img->image[row][column];
        }
    }
}

void freeImage(Image *img)
{
    for (int i = 0; i < img->rows; ++i)
    {
        free(img->image[i]);
    }

    free(img->image);
}
