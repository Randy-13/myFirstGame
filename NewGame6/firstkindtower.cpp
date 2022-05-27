#include "firstkindtower.h"

firstKindTower::firstKindTower() : Tower()
{
    this->attackR = 180;
    this->aggressivity = 10;
    updateCost(180);
}

firstKindTower::firstKindTower(int x,int y,int mapX,int mapY,QString picturePath) : Tower(x,y,mapX,mapY,picturePath)
{
    this->attackR = 180;
    this->aggressivity = 10;
    updateCost(180);
}
