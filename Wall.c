#include "Wall.h"

point3 mainFrontWall[4] = {
    { 3, 0, 6 },
    { -3, 0, 6 },
    { -3, 2, 6 },
    { 3, 2, 6 },
};

point3 mainLeftSide[4] = {
    { 3, 0, 1.5 },
    { 1.5, 0, 1.5 },
    { 1.5, 2, 1.5 },
    { 3, 2, 1.5 },
};

point3 mainRightSide[4] = {
    { -1.5, 0, 1.5 },
    { -3, 0, 1.5 },
    { -3, 2, 1.5 },
    { -1.5, 2, 1.5 },
};

point3 mainLeftWall[4] = {
    { 3, 0, 6 },
    { 3, 0, 1.5 },
    { 3, 2, 1.5 },
    { 3, 2, 6 }
};

point3 mainRightWall[4] = {
    { -3, 0, 6 },
    { -3, 0, 1.5 },
    { -3, 2, 1.5 },
    { -3, 2, 6 }
};

point3 mainFloor[4] = {
    { 3, 0, 6 },
    { -3, 0, 6 },
    { -3, 0, 1.5 },
    { 3, 0, 1.5 }
};

point3 backLeftWall[4] = {
    { 1.5, 0, -10 },
    { 1.5, 0, 1.5 },
    { 1.5, 2, 1.5 },
    { 1.5, 2, -10 }
};

point3 backRightWall[4] = {
    { -1.5, 0, -10 },
    { -1.5, 0, 1.5 },
    { -1.5, 2, 1.5 },
    { -1.5, 2, -10 }
};

point3 backWall[4] = {
    { 1.5, 0, -10 },
    { -1.5, 0, -10 },
    { -1.5, 2, -10 },
    { 1.5, 2, -10 }
};

point3 backFloor[4] = {
    { 1.5, 0, 1.5 },
    { -1.5, 0, 1.5 },
    { -1.5, 0, -10 },
    { 1.5, 0, -10 }
};

void drawFace(point3 face[4], GLenum mode)
{
    if (mode == GL_CCW)
    {
        glBegin(GL_POLYGON);
            glNormal3fv(face[0]);
            glVertex3fv(face[0]);
            glNormal3fv(face[1]);
            glVertex3fv(face[1]);
            glNormal3fv(face[2]);
            glVertex3fv(face[2]);
            glNormal3fv(face[3]);
            glVertex3fv(face[3]);
        glEnd();
    }
    else if (mode == GL_CW)
    {
        glBegin(GL_POLYGON);
            glNormal3fv(face[3]);
            glVertex3fv(face[3]);
            glNormal3fv(face[2]);
            glVertex3fv(face[2]);
            glNormal3fv(face[1]);
            glVertex3fv(face[1]);
            glNormal3fv(face[0]);
            glVertex3fv(face[0]);
        glEnd();
    }
}

void drawWalls()
{
    drawFace(mainFrontWall, GL_CCW);
    drawFace(mainLeftSide, GL_CW);
    drawFace(mainRightSide, GL_CW);
    drawFace(mainLeftWall, GL_CW);
    drawFace(mainRightWall, GL_CCW);
    drawFace(backLeftWall, GL_CCW);
    drawFace(backRightWall, GL_CW);
    drawFace(backWall, GL_CW);
    drawFace(mainFloor, GL_CW);
    drawFace(backFloor, GL_CW);
}

void readPlane(point3 face[4], BoundingBox *bBox)
{
    bBox->minExtent.x = face[0][0];
    bBox->minExtent.y = face[0][1];
    bBox->minExtent.z = face[0][2];

    bBox->maxExtent.x = face[0][0];
    bBox->maxExtent.y = face[0][1];
    bBox->maxExtent.z = face[0][2];


    for (int i = 0; i < 4; ++i)
    {
        bBox->minExtent.x = (face[i][0] < bBox->minExtent.x) ? face[i][0] : bBox->minExtent.x;
        bBox->minExtent.y = (face[i][1] < bBox->minExtent.y) ? face[i][1] : bBox->minExtent.y;
        bBox->minExtent.z = (face[i][2] < bBox->minExtent.z) ? face[i][2] : bBox->minExtent.z;

        bBox->maxExtent.x = (face[i][0] > bBox->maxExtent.x) ? face[i][0] : bBox->maxExtent.x;
        bBox->maxExtent.y = (face[i][1] > bBox->maxExtent.y) ? face[i][1] : bBox->maxExtent.y;
        bBox->maxExtent.z = (face[i][2] > bBox->maxExtent.z) ? face[i][2] : bBox->maxExtent.z;
    }
}

void readPlanes(Wall *wall)
{
    readPlane(mainFrontWall, &wall->bPlanes[0]);
    readPlane(mainLeftSide, &wall->bPlanes[1]);
    readPlane(mainRightSide, &wall->bPlanes[2]);
    readPlane(mainLeftWall, &wall->bPlanes[3]);
    readPlane(mainRightWall, &wall->bPlanes[4]);
    readPlane(backLeftWall, &wall->bPlanes[5]);
    readPlane(backRightWall, &wall->bPlanes[6]);
    readPlane(backWall, &wall->bPlanes[7]);
    readPlane(mainFloor, &wall->bPlanes[8]);
    readPlane(backFloor, &wall->bPlanes[9]);
}

void resizePlanes(Wall *wall)
{
    wall->bPlanes[0].maxExtent.z += 0.1;
    wall->bPlanes[1].maxExtent.z += 0.1;
    wall->bPlanes[2].maxExtent.z += 0.1;
    wall->bPlanes[3].maxExtent.x += 0.1;
    wall->bPlanes[4].maxExtent.x += 0.1;
    wall->bPlanes[5].maxExtent.x += 0.1;
    wall->bPlanes[6].maxExtent.x += 0.1;
    wall->bPlanes[7].maxExtent.z += 0.1;
}
