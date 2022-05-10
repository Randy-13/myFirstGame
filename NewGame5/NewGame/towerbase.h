#ifndef TOWERBASE_H
#define TOWERBASE_H

#include "base.h"
#include <QPushButton>

class towerBase : public QWidget
{
public:
    towerBase();
    towerBase(int x,int y,int mapX,int mapY);
    int getMapX();
    int getMapY();
    int getX();
    int getY();
private:
    int x;
    int y;
    int mapX;
    int mapY;
};

#endif // TOWERBASE_H
