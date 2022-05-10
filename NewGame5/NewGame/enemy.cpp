#include "enemy.h"

Enemy::Enemy() : Melee()
{

}

Enemy::Enemy(int x,int y,int mapX,int mapY) : Melee(x,y,mapX,mapY)
{
    this->type = "Enemy";
    this->setHealthValue();
    this->setAggressivity();
}

void Enemy::setAggressivity()
{
    this->aggressivity = 25;
}

QString Enemy::getType()
{
    return this->type;
}

void Enemy::setHealthValue()
{
    this->healthValue = 100;
    this->nowHealthValue = healthValue;
}
