#include "soldiers.h"

Soldiers::Soldiers() : Melee()
{

}

Soldiers::Soldiers(int x,int y,int mapX,int mapY) : Melee(x,y,mapX,mapY)
{
    this->type = "Soldiers";
    this->setAggressivity();
    this->setHealthValue();
}

void Soldiers::setAggressivity()
{
    this->aggressivity = 35;
}

QString Soldiers::getType()
{
    return this->type;
}

void Soldiers::setHealthValue()
{
    this->healthValue = 150;
    this->nowHealthValue = healthValue;
}
