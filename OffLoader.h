#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED
#include <stdio.h>
#include "Object3D.h"

FILE * openFile(char *fileName, char *fileType);

void closeFile(FILE * File);

Object3D readOFFFile(char *fileName);


#endif // FILEIO_H_INCLUDED
