#include "enemysorcerer.h"

enemySorcerer::enemySorcerer() : flyObject()
{
    this->flyType = "Enemy";
    this->attackR = 180;
    this->aggressivity = 3;
    this->healthValue = 250;
    this->nowHealthValue = healthValue;
    this->cure = 18;
}

enemySorcerer::enemySorcerer(int x,int y,int mapX,int mapY) : flyObject(x,y,mapX,mapY)
{
    this->flyType = "Enemy";
    this->attackR = 180;
    this->aggressivity = 3;
    this->healthValue = 250;
    this->nowHealthValue = healthValue;
    this->cure = 18;
}

int enemySorcerer::getCure()
{
    return this->cure;
}
