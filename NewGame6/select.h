#ifndef SELECT_H
#define SELECT_H

#include <QVector>
#include <QString>
#include "towerbase.h"

class Select
{
public:
    ~Select();
    Select(int x,int y,int mapX,int mapY);
    int getMapX();
    int getMapY();
    int getX();
    int getY();
    void updatePreTb(towerBase * tptb);
    towerBase * getPreTb();
    QString picturePath[3];
private:
    int x;
    int y;
    int mapX;
    int mapY;
    towerBase * preTb;
};

#endif // SELECT_H
