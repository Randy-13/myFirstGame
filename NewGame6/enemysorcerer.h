#ifndef ENEMYSORCERER_H
#define ENEMYSORCERER_H

#include "flyobject.h"
class enemySorcerer : public flyObject
{
public:
    enemySorcerer();
    enemySorcerer(int x,int y,int mapX,int mapY);
    int getCure();
private:
    int cure;
};

#endif // ENEMYSORCERER_H
