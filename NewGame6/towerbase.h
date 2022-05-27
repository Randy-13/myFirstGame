#ifndef TOWERBASE_H
#define TOWERBASE_H

#include "base.h"
#include <QPushButton>

class towerBase : public QWidget
{
public:
    towerBase();
    towerBase(int x,int y,int mapX,int mapY);
    void updateIfIsUsed(bool update);
    int getMapX();
    int getMapY();
    int getX();
    int getY();
    bool getIfIsUsed();
private:
    int x;
    int y;
    int mapX;
    int mapY;
    bool isUsed;
};

#endif // TOWERBASE_H
