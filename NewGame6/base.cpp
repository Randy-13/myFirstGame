#include "base.h"

Base::Base()
{
    this->x = 0;
    this->y = 0;
}

Base::Base(int x,int y,int mapX,int mapY)
{
    this->x = x;
    this->y = y;
    this->mapX = mapX;
    this->mapY = mapY;
}

int Base::getX()
{
    return this->x;
}

int Base::getY()
{
    return this->y;
}

int Base::getMapX()
{
    return this->mapX;
}

int Base::getMapY()
{
    return this->mapY;
}
