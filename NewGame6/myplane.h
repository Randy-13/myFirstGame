#ifndef MYPLANE_H
#define MYPLANE_H

#include "flyobject.h"
class myPlane : public flyObject
{
public:
    myPlane();
    myPlane(int x,int y,int mapX,int mapY);
};

#endif // MYPLANE_H
