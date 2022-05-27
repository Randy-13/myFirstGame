#include "tower.h"

Tower::Tower()
{
    this->x = 0;
    this->y = 0;
    this->mapX = 0;
    this->mapY = 0;
    this->live = true;
    this->attackEventPos.resize(4);
    for(int i = 0; i < 4; i++)
    {
        this->attackEventPos[i] = -1;
    }
}

Tower::Tower(int x,int y,int mapX,int mapY,QString picturePath)
{
    this->x = x;
    this->y = y;
    this->mapX = mapX;
    this->mapY = mapY;
    this->live = true;
    this->picturePath = picturePath;
    this->attackEventPos.resize(4);
    for(int i = 0; i < 4; i++)
    {
        this->attackEventPos[i] = -1;
    }
}

void Tower::updateCost(int cost)
{
    this->cost = cost;
}

int Tower::getCost()
{
    return this->cost;
}

int Tower::getMapX()
{
    return this->mapX;
}

int Tower::getMapY()
{
    return this->mapY;
}

int Tower::getX()
{
    return this->x;
}

int Tower::getY()
{
    return this->y;
}

QString Tower::getPicturePath()
{
    return this->picturePath;
}

int Tower::getAggressivity()
{
    return this->aggressivity;
}

bool Tower::checkAttackRange(int enemyMapX,int enemyMapY)
{
    int tx = enemyMapX-this->mapX;
    int ty = enemyMapY-this->mapY;
    //qDebug() << this->mapX << this->mapY << enemyMapX << enemyMapY << tx << ty << this->attackR;
    if(tx * tx + ty * ty <= this->attackR * this->attackR)
    {
        return true;
    }
    return false;
}

bool Tower::checkIfShowRange()
{
    return this->showRange;
}

 void Tower::updateIfShowRange(bool update)
 {
     this->showRange = update;
 }

 int Tower::getAttackR()
 {
     return this->attackR;
 }
