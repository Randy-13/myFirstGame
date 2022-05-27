#include "thirdkindtower.h"

thirdKindTower::thirdKindTower() : Tower()
{
    this->attackR = 200;
    this->aggressivity = 20;
    updateCost(500);
}

thirdKindTower::thirdKindTower(int x,int y,int mapX,int mapY,QString picturePath): Tower(x, y, mapX, mapY, picturePath)
{
    this->attackR = 200;
    this->aggressivity = 20;
    updateCost(500);
}
