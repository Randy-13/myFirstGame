#include "flyobject.h"

flyObject::flyObject()
{
    this->attackEventPos.resize(4);
    for(int i = 0; i < 4; i++)
    {
        this->attackEventPos[i] = -1;
    }
}

flyObject::flyObject(int x,int y,int mapX,int mapY) : Melee(x,y,mapX,mapY)
{
    this->attackEventPos.resize(4);
    for(int i = 0; i < 4; i++)
    {
        this->attackEventPos[i] = -1;
    }
}

QString flyObject::getType()
{
    return this->flyType;
}

bool flyObject::checkAttackRange(int enemyMapX,int enemyMapY)
{
    int tx = enemyMapX-this->getMapPosX();
    int ty = enemyMapY-this->getMapPosY();
   // qDebug() << this->getMapPosX() << this->getMapPosY() << enemyMapX << enemyMapY << tx << ty << this->attackR;
    if(tx * tx + ty * ty <= this->attackR * this->attackR)
    {
        return true;
    }
    return false;
}
