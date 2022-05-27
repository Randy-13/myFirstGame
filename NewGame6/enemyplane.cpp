#include "enemyplane.h"

enemyPlane::enemyPlane() : flyObject()
{
    this->flyType = "Enemy";
    this->attackR = 120;
    this->aggressivity = 5;
    this->healthValue = 120;
    this->nowHealthValue = healthValue;
}

enemyPlane::enemyPlane(int x,int y,int mapX,int mapY) : flyObject(x, y, mapX, mapY)
{
    this->flyType = "Enemy";
    this->attackR = 120;
    this->aggressivity = 5;
    this->healthValue = 120;
    this->nowHealthValue = healthValue;
}
