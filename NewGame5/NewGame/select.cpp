#include "select.h"


Select::Select(int x,int y,int mapX,int mapY)
{
    this->x = x;
    this->y = y;
    this->mapX = mapX;
    this->mapY = mapY;
}

Select::~Select()
{

}

int Select::getMapX()
{
    return this->mapX;
}

int Select::getMapY()
{
    return this->mapY;
}

int Select::getX()
{
    return this->x;
}

int Select::getY()
{
    return this->y;
}
