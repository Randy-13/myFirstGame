#include "mybase.h"

myBase::myBase()
{
    this->x = 0;
    this->y = 0;
}

myBase::myBase(int x,int y)
{
    this->x = x;
    this->y = y;
}
int myBase::getX()
{
    return this->x;
}
int myBase::getY()
{
    return this->y;
}
