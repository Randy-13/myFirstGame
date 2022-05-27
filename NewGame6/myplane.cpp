#include "myplane.h"

myPlane::myPlane()
{
    this->flyType = "Soldiers";
    this->attackR = 120;
    this->aggressivity = 8;
    this->healthValue = 120;
    this->nowHealthValue = healthValue;
    this->updateCost(150);
}

myPlane::myPlane(int x,int y,int mapX,int mapY) : flyObject(x, y, mapX, mapY)
{
    this->flyType = "Soldiers";
    this->attackR = 120;
    this->aggressivity = 8;
    this->healthValue = 120;
    this->nowHealthValue = healthValue;
    this->updateCost(150);
}
