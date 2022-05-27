#include "select.h"


Select::Select(int x,int y,int mapX,int mapY)
{
    this->x = x;
    this->y = y;
    this->mapX = mapX;
    this->mapY = mapY;
    this->preTb = NULL;
}

Select::~Select()
{
    this->preTb = NULL;
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

void Select::updatePreTb(towerBase * tptb)
{
    this->preTb = tptb;
}

towerBase * Select::getPreTb()
{
    return this->preTb;
}
