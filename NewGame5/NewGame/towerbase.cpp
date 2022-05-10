#include "towerbase.h"

towerBase::towerBase()
{
    this->x = 0;
    this->y = 0;
    this->mapX = 0;
    this->mapY = 0;
}

towerBase::towerBase(int x,int y,int mapX,int mapY)
{
    this->x = x;
    this->y = y;
    this->mapX = mapX;
    this->mapY = mapY;
}

int towerBase::getMapX()
{
    return this->mapX;
}

int towerBase::getMapY()
{
    return this->mapY;
}

int towerBase::getX()
{
    return this->x;
}
int towerBase::getY()
{
    return this->y;
}
