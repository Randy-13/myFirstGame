#include "enemy.h"

Enemy::Enemy()
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

Enemy::Enemy(int x,int y,int mapX,int mapY)
{
    this->live = true;
    this->x = x;
    this->y = y;
    this->prex = x;
    this->prey = y;
    this->mapPosX = mapX;
    this->mapPosY = mapY;
}

void Enemy::initMovePathArr(int ti,int tj)
{
    this->movePathArr.resize(ti);
    for(int i = 0; i < ti; i++)
    {
        this->movePathArr[i].resize(tj,true);
    }
}

int Enemy::getX()
{
    return this->x;
}

int Enemy::getY()
{
    return this->y;
}

QChar Enemy::getMoveDirection()
{
    return this->moveDirection;
}

bool Enemy::getPathCondition(int ti,int tj)
{
    return this->movePathArr[ti][tj];
}

int Enemy::getPreX()
{
    return this->prex;
}

int Enemy::getPreY()
{
    return this->prey;
}

int Enemy::getMapPosX()
{
    return this->mapPosX;
}

int Enemy::getMapPosY()
{
    return this->mapPosY;
}

bool Enemy::getLiveState()
{
    return this->live;
}

void Enemy::updateX(int x)
{
    this->prex = this->x;
    this->x = x;
}

void Enemy::updateY(int y)
{
    this->prey = this->y;
    this->y = y;
}

void Enemy::updateLiveState(bool check)
{
    this->live = check;
}

void Enemy::updateMoveDirection(QChar dir)
{
    this->moveDirection = dir;
}

void Enemy::updatePathCondition(int ti,int tj,bool chang)
{
    this->movePathArr[ti][tj] = chang;
}

void Enemy::MapPosLeftMove()
{
    this->mapPosX -= 1;
}

void Enemy::MapPosRightMove()
{
    this->mapPosX += 1;
}

void Enemy::MapPosUpMove()
{
    this->mapPosY -= 1;
}

void Enemy::MapPosDownMove()
{
    this->mapPosY += 1;
}
