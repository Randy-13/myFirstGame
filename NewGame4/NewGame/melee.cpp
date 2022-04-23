#include "melee.h"

Melee::Melee()
{
    this->live = true;
    this->x = 0;
    this->y = 0;
    this->prex = 0;
    this->prey = 0;
    this->moveDirection = 'p';
    this->mapPosX = 0;
    this->mapPosY = 0;
}

Melee::Melee(int x,int y,int mapX,int mapY)
{
    this->live = true;
    this->x = x;
    this->y = y;
    this->prex = x;
    this->prey = y;
    this->mapPosX = mapX;
    this->mapPosY = mapY;
}

void Melee::initMovePathArr(int ti,int tj)
{
    this->movePathArr.resize(ti);
    for(int i = 0; i < ti; i++)
    {
        this->movePathArr[i].resize(tj,true);
    }
}

int Melee::getX()
{
    return this->x;
}

int Melee::getY()
{
    return this->y;
}

QChar Melee::getMoveDirection()
{
    return this->moveDirection;
}

bool Melee::getPathCondition(int ti,int tj)
{
    return this->movePathArr[ti][tj];
}

int Melee::getPreX()
{
    return this->prex;
}

int Melee::getPreY()
{
    return this->prey;
}

int Melee::getMapPosX()
{
    return this->mapPosX;
}

int Melee::getMapPosY()
{
    return this->mapPosY;
}

bool Melee::getLiveState()
{
    return this->live;
}

int Melee::getHealvalue()
{
    return this->healthValue;
}

int Melee::getAggressivity()
{
    return this->aggressivity;
}

void Melee::updateX(int x)
{
    this->prex = this->x;
    this->x = x;
}

void Melee::updateY(int y)
{
    this->prey = this->y;
    this->y = y;
}

void Melee::updateLiveState(bool check)
{
    this->live = check;
}

void Melee::updateMoveDirection(QChar dir)
{
    this->moveDirection = dir;
}

 bool Melee::updateHealthValue(int num)
 {
     int tpValue = this->healthValue;
     if(tpValue + num >= 0)
     {
         this->healthValue += num;
         return true;
     }else{
         return false;
     }
 }

void Melee::updatePathCondition(int ti,int tj,bool check)
{
    this->movePathArr[ti][tj] = check;
}

void Melee::setAggressivity()
{
    this->aggressivity = 0;
}

void Melee::setHealthValue()
{
    this->healthValue = 0;
}

void Melee::MapPosLeftMove()
{
    this->mapPosX -= 1;
}

void Melee::MapPosRightMove()
{
    this->mapPosX += 1;
}

void Melee::MapPosUpMove()
{
    this->mapPosY -= 1;
}

void Melee::MapPosDownMove()
{
    this->mapPosY += 1;
}
