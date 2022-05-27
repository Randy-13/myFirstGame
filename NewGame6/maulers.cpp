#include "maulers.h"

Maulers::Maulers()
{
    this->type = "Soldiers";
    this->setAggressivity();
    this->setHealthValue();
    this->updateCost(200);
}

Maulers::Maulers(int x,int y,int mapX,int mapY) : Melee(x,y,mapX,mapY)
{
    this->type = "Soldiers";
    this->setAggressivity();
    this->setHealthValue();
    this->updateCost(200);
}

void Maulers::setAggressivity()
{
     this->aggressivity = 1;
}

QString Maulers::getType()
{
    return this->type;
}

void Maulers::setHealthValue()
{
    this->healthValue = 800;
    this->nowHealthValue = healthValue;
}
