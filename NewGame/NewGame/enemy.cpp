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
