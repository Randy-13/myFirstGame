#include "map.h"

SubMap::SubMap()
{
    this->x = 0;
    this->y = 0;
    this->mapType = 4;        //设置地图块种类数
}

int SubMap::getX()
{
    return this->x;
}

int SubMap::getY()
{
    return this->y;
}

bool SubMap::updateXY(int tx,int ty)
{
    this->x = tx;
    this->y = ty;
    return true;
}
