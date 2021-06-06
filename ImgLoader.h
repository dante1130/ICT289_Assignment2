#ifndef IMGLOADER_H_INCLUDED
#define IMGLOADER_H_INCLUDED

#include "Image.h"
#include "OffLoader.h" // Just for functions for reading and closing files

void readImage(char *imageName, int maxRows, int maxColumns, Image *image);

#endif // IMGLOADER_H_INCLUDED
