#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "flyobject.h"
class enemyPlane : public flyObject
{
public:
    enemyPlane();
    enemyPlane(int x,int y,int mapX,int mapY);
};

#endif // ENEMYPLANE_H
