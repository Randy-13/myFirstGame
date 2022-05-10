#include "base.h"

Base::Base()
{
    this->x = 0;
    this->y = 0;
}

Base::Base(int x,int y)
{
    this->x = x;
    this->y = y;
}

int Base::getX()
{
    return this->x;
}

int Base::getY()
{
    return this->y;
}
