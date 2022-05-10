#ifndef ENEMY_H
#define ENEMY_H

#include <QChar>
#include <QString>
#include <QVector>
#include "melee.h"

class Enemy : public Melee
{
public:
    Enemy();
    Enemy(int x,int y,int mapX,int mapY);
    void setAggressivity();
    QString getType();
    void setHealthValue();
private:

};

#endif // ENEMY_H
