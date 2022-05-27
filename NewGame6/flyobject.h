#ifndef FLYOBJECT_H
#define FLYOBJECT_H

#include "melee.h"
#include <QDebug>

class flyObject : public Melee
{
public:
    flyObject();
    flyObject(int x,int y,int mapX,int mapY);
    bool checkAttackRange(int enemyMapX,int enemyMapY);
    QString getPicturePath();
    QVector<int> attackEventPos;           //飞行物攻击锚点
    virtual QString getType();
private:

protected:
     QString flyType;
     int attackR;
     QString picturePath;
};

#endif // FLYOBJECT_H
