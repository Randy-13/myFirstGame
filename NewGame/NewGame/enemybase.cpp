#include "enemybase.h"

enemyBase::enemyBase()
{
   this->x = 0;
   this->y = 0;
}

enemyBase::enemyBase(int x,int y)
{
   this->x = x;
   this->y = y;
}

int enemyBase::getX()
{
    return this->x;
}

int enemyBase::getY()
{
    return this->y;
}
