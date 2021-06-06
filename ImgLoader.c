#include "ImgLoader.h"

void readImage(char *imageName, int maxRows, int maxColumns, Image *img)
{
    int charin;

    FILE * file;

    if ((file = fopen(imageName, "rb")) == NULL)  /* open failed */
    {
        puts("*** Can't open input file - please check file name typed!\n ");
        charin = getchar();
        exit(1);   /* terminate execution */
    }

    img->rows = maxRows;
    img->columns = maxColumns;

    img->image = (pixel *) malloc(sizeof(pixel) * img->rows);

    /* reaching this line of code means file opened successfully,
    now read file contents into image array */
    for (int row = 0; row < img->rows; ++row)
    {
        img->image[row] = (pixel *) malloc(sizeof(pixel) * img->columns);
        for (int column = 0; column < img->columns; ++column)
        {
            if ((charin = fgetc(file)) == EOF)   /* read failed */
            {
                printf("***File reading failed! \n");
                charin = getchar();
                exit(1);    /* terminate execution */
            }
            img->image[row][column] = charin;
        }
    }

    closeFile(file);
}


