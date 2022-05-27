#include "secondkindtower.h"

secondKindTower::secondKindTower() : Tower()
{
    this->attackR = 250;
    this->aggressivity = 13;
    updateCost(350);
}

secondKindTower::secondKindTower(int x,int y,int mapX,int mapY,QString picturePath) : Tower(x, y, mapX, mapY, picturePath)
{
    this->attackR = 250;
    this->aggressivity = 13;
    updateCost(350);
}
