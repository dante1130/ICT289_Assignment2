#include "OffLoader.h"

FILE * openFile(char *fileName, char *fileType)
{
    FILE * file;

    file = fopen(fileName, fileType);

    if (file == NULL)
    {
        perror("File opening failed!");
    }
    else
    {
        printf("File opening successful!\n");
    }
    return file;
}

void closeFile(FILE * File)
{
    if (fclose(File) != 0)
    {
        printf("File closing failed!\n");
    }
    else
    {
        printf("File closed successfully!\n");
    }

    return;
}

Object3D readOFFFile(char *fileName)
{
    FILE *file = openFile(fileName, "r");
    int buffer;
    char *strBuffer;
    Object3D obj3D;

    // OFF
    fscanf(file, "%s", &strBuffer);

    // nvert and nfaces
    fscanf(file, "%d %d %d", &obj3D.nvert, &obj3D.nfaces, &buffer);

    // dynamically allocating memory for vertices and faces
    obj3D.vertices = (Vector3 *) malloc(obj3D.nvert * sizeof(Vector3));
    obj3D.faces = (Faces *) malloc(obj3D.nfaces * sizeof(Faces));

    // vertices
    for (int i = 0; i < obj3D.nvert; ++i)
    {
        fscanf(file, "%f %f %f", &obj3D.vertices[i].x, &obj3D.vertices[i].y, &obj3D.vertices[i].z);
    }

    // faces
    for (int i = 0; i < obj3D.nfaces; ++i)
    {
        fscanf(file, "%d", &obj3D.faces[i].numPoints);

        obj3D.faces[i].points = (GLint *) malloc(obj3D.faces[i].numPoints * sizeof(GLint));

        for (int j = 0; j < obj3D.faces[i].numPoints; ++j)
        {
            fscanf(file, "%d", &obj3D.faces[i].points[j]);
        }
    }

    closeFile(file);
    return obj3D;
}
