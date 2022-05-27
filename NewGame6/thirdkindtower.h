#ifndef THIRDKINDTOWER_H
#define THIRDKINDTOWER_H

#include "tower.h"

class thirdKindTower : public Tower
{
public:
    thirdKindTower();
    thirdKindTower(int x,int y,int mapX,int mapY,QString picturePath);
};

#endif // THIRDKINDTOWER_H
